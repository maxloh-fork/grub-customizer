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



namespace Gc { namespace Model { namespace ContentParser { class LinuxIso :
	public Gc::Model::ContentParser::AbstractParser,
	public Gc::Common::Regex::GenericConnection,
	public Gc::Model::Device::DeviceMapConnection,
	public Gc::Model::Device::MountTableConnection,
	public Gc::Model::Device::DeviceDataListConnection
{
	private: static const char* _regex;
	private: std::string sourceCode;

	public: void parse(std::string const& sourceCode)
	{
		this->sourceCode = sourceCode;
		try {
			std::vector<std::string> result = this->regexEngine->match(Gc::Model::ContentParser::LinuxIso::_regex, this->sourceCode, '\\', '_');
	
			//check partition indices by uuid
			Gc::Model::Device::DeviceMapPartitionIndex pIndex = this->deviceMap->getHarddriveIndexByPartitionUuid(result[3]);
			if (pIndex.hddNum != result[1] || pIndex.partNum != result[2]){
				throw Gc::Common::Exception::ParserException("parsing failed - hdd num check", __FILE__, __LINE__);
			}
	
			//check if the iso filepaths are the same
			if (this->unescape(result[4]) != this->unescape(result[6]))
				throw Gc::Common::Exception::ParserException("parsing failed - iso filepaths are different", __FILE__, __LINE__);

			//assign data
			this->options["partition_uuid"] = result[3];
			this->options["linux_image"] = Gc::Common::Functions::str_replace("(loop)", "", this->unescape(result[5]));
			this->options["initramfs"] = Gc::Common::Functions::str_replace("(loop)", "", this->unescape(result[8]));
			this->options["iso_path"] = this->unescape(result[4]);
			this->options["iso_path_full"] = "";
			this->options["other_params"] = Gc::Common::Functions::ltrim(result[7], " ");

			try {
				std::string device = this->deviceDataList->getDeviceByUuid(this->options["partition_uuid"]);
				this->options["iso_path_full"] = Gc::Common::Functions::rtrim(this->mountTable->findByDevice(device).mountpoint, "/") + "/" + Gc::Common::Functions::ltrim(this->options["iso_path"], "/");
				if (!this->_fileExists(this->options["iso_path_full"])) {
					throw Gc::Common::Exception::ItemNotFoundException("iso file '" + this->options["iso_path_full"] + "'not found!", __FILE__, __LINE__);
				}
				this->options.erase("partition_uuid");
				this->options.erase("iso_path");
			} catch (Gc::Common::Exception::ItemNotFoundException const& e) {
				// partition not mounted or file not found
				this->options.erase("iso_path_full");
			}


		} catch (Gc::Common::Exception::RegExNotMatchedException const& e) {
			throw Gc::Common::Exception::ParserException("parsing failed - RegEx not matched", __FILE__, __LINE__);
		}
	}

	public: std::string buildSource() const
	{
		std::string partitionUuid, isoPath;

		if (this->options.find("iso_path_full") != this->options.end()) {
			std::string realIsoPath = this->_realpath(this->options.at("iso_path_full"));
			Gc::Model::Device::MountTableMountpoint& mountpoint = this->mountTable->getByFilePath(realIsoPath);
			partitionUuid = (*this->deviceDataList)[mountpoint.device]["UUID"];
			isoPath = realIsoPath.substr(mountpoint.mountpoint.size());
		} else {
			partitionUuid = this->options.at("partition_uuid");
			isoPath = this->options.at("iso_path");
		}

		try {
			Gc::Model::Device::DeviceMapPartitionIndex pIndex = this->deviceMap->getHarddriveIndexByPartitionUuid(partitionUuid);
			std::map<int, std::string> newValues;
			newValues[1] = pIndex.hddNum;
			newValues[2] = pIndex.partNum;
			newValues[3] = partitionUuid;
			newValues[4] = this->escape(isoPath);
			newValues[5] = this->escape("(loop)" + this->options.at("linux_image"));
			newValues[6] = this->escape(isoPath);
			newValues[7] = this->options.at("other_params").size() ? " " + this->options.at("other_params") : "";
			newValues[8] = this->escape("(loop)" + this->options.at("initramfs"));

			std::string result;

			result = this->regexEngine->replace(Gc::Model::ContentParser::LinuxIso::_regex, this->sourceCode, newValues, '\\', '_');
			this->regexEngine->match(Gc::Model::ContentParser::LinuxIso::_regex, result, '\\', '_');

			return result;
		} catch (Gc::Common::Exception::RegExNotMatchedException const& e) {
			throw Gc::Common::Exception::ParserException("parsing failed - RegEx not matched", __FILE__, __LINE__);
		}
	}


	public: void buildDefaultEntry()
	{
		std::string defaultEntry =
			"set root='(hd0,0)'\n"
			"search --no-floppy --fs-uuid --set=root 000000000000000000\n"
			"loopback loop ___\n"
			"linux (loop)___ boot=casper iso-scan/filename=___\n"
			"initrd (loop)___\n";

		assert(this->regexEngine->match(Gc::Model::ContentParser::LinuxIso::_regex, defaultEntry, '\\', '_').size() > 0);

		this->sourceCode = defaultEntry;

		this->options.clear();
		this->options["linux_image"] = "/casper/vmlinuz";
		this->options["initramfs"] = "/casper/initrd.lz";
		this->options["iso_path_full"] = "";
		this->options["other_params"] = "quiet splash locale=en_US bootkbd=us console-setup/layoutcode=us noeject --";
	}

};}}}

const char* Gc::Model::ContentParser::LinuxIso::_regex =
	"[ \t]*set root='\\(hd([0-9]+)[^0-9]+([0-9]+)\\)'\\n"
	"[ \t]*search[ \\t]+--no-floppy[ \\t]+--fs-uuid[ \\t]+--set(?:=root)? ([-0-9a-fA-F]+)\\n"
	"[ \t]*loopback[ \\t]+loop[ \t]+(\"[^\"]*\"|[^ \\t]+)\\n"
	"[ \t]*linux[ \\t]+(\"\\(loop\\)[^\"]*\"|\\(loop\\)[^ \\t]*)[ \\t]+boot=casper iso-scan/filename=(\"[^\"]*\"|[^ \\t]+)(.*)\\n"
	"[ \t]*initrd[ \\t]+(\"\\(loop\\)[^\"]*\"|\\(loop\\)[^ \\t]*)";

