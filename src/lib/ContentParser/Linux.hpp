/*
 * Copyright (C) 2010-2011 Daniel Richter <danielrichter2007@web.de>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef CONTENT_PARSER_LINUX_H_
#define CONTENT_PARSER_LINUX_H_
#include "../../Model/DeviceMap.hpp"
#include "../Regex.hpp"
#include "Abstract.hpp"

class ContentParser_Linux :
	public ContentParser_Abstract,
	public Regex_RegexConnection
{
	static const char* _regex;
	Model_DeviceMap& deviceMap;
	std::string sourceCode;
public:
	ContentParser_Linux(Model_DeviceMap& deviceMap) : deviceMap(deviceMap)
	{}

	void parse(std::string const& sourceCode) {
		this->sourceCode = sourceCode;
		try {
			std::vector<std::string> result = this->regexEngine->match(ContentParser_Linux::_regex, sourceCode);
	
			//check partition indices by uuid
			Model_DeviceMap_PartitionIndex pIndex = deviceMap.getHarddriveIndexByPartitionUuid(result[6]);
			if (pIndex.hddNum != result[1] || pIndex.partNum != result[2]){
				throw ParserException("parsing failed - hdd num check", __FILE__, __LINE__);
			}
	
			//check if the uuids (Kernel <-> search command) are the same
			if (result[3] != result[6])
				throw ParserException("parsing failed - uuid different", __FILE__, __LINE__);
	
			//assign data
			this->options["partition_uuid"] = result[6];
			this->options["linux_image"] = result[5];
			this->options["initramfs"] = result[8];
		} catch (RegExNotMatchedException const& e) {
			throw ParserException("parsing failed - RegEx not matched", __FILE__, __LINE__);
		}
	}

	std::string buildSource() const {
		Model_DeviceMap_PartitionIndex pIndex = deviceMap.getHarddriveIndexByPartitionUuid(this->options.at("partition_uuid"));
		std::map<int, std::string> newValues;
		newValues[1] = pIndex.hddNum;
		newValues[2] = pIndex.partNum;
		newValues[3] = this->options.at("partition_uuid");
		newValues[5] = this->options.at("linux_image");
		newValues[6] = this->options.at("partition_uuid");
		newValues[8] = this->options.at("initramfs");
	
		std::string result = this->regexEngine->replace(ContentParser_Linux::_regex, this->sourceCode, newValues);
	
		//check the new string. If they aren't matchable anymore (evil input), do a rollback
		try {
			this->regexEngine->match(ContentParser_Linux::_regex, result);
		} catch (RegExNotMatchedException const& e) {
			this->log("Ignoring data - doesn't match", Logger::ERROR);
			result = this->sourceCode;
		}
		return result;
	}

	void buildDefaultEntry(std::string const& partition_uuid) {
		std::string defaultEntry = "\
		set root='(hd0,0)'\n\
		search --no-floppy --fs-uuid --set=root 000000000000\n\
		linux /vmlinuz root=UUID=000000000000 \n\
		initrd /initrd.img";
		Model_DeviceMap_PartitionIndex pIndex = this->deviceMap.getHarddriveIndexByPartitionUuid(partition_uuid);
		std::map<int, std::string> newValues;
		newValues[1] = pIndex.hddNum;
		newValues[2] = pIndex.partNum;
		newValues[3] = partition_uuid;
		newValues[6] = partition_uuid;
	
		this->parse(this->regexEngine->replace(ContentParser_Linux::_regex, defaultEntry, newValues));
	}

};

const char* ContentParser_Linux::_regex = "\
[ \t]*set root='\\(hd([0-9]+)[^0-9]+([0-9]+)\\)'\\n\
[ \t]*search[ \t]+--no-floppy[ \t]+--fs-uuid[ \t]+--set(?:=root)? ([-0-9a-fA-F]+)\\n\
([ \t]*echo[ \t]+.*\n)?\
[ \t]*linux[ \t]+([^ \t]+)[ \t]+root=UUID=([-0-9a-fA-F]+) .*\\n\
([ \t]*echo[ \t]+.*\n)?\
[ \t]*initrd[ \t]+([^ \\n]+)[ \\n\t]*$\
";

#endif /* CONTENT_PARSER_LINUX_H_ */