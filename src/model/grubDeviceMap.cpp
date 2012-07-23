#include "grubDeviceMap.h"

GrubDeviceMap::GrubDeviceMap(GrubEnv const& env) {
	this->env = &env;
}
SmartFileHandle GrubDeviceMap::getFileHandle() const {
	SmartFileHandle result;
	try {
		result.open(env->devicemap_file, "r", SmartFileHandle::TYPE_FILE);
	} catch (SmartFileHandle::Exception e) {
		result.open(env->mkdevicemap_cmd, "r", SmartFileHandle::TYPE_COMMAND);
	}
	return result;
}

GrubPartitionIndex GrubDeviceMap::getHarddriveIndexByPartitionUuid(std::string partitionUuid) const {
	GrubPartitionIndex result;
	char deviceBuf[101];
	int size = readlink((this->env->cfg_dir_prefix + "/dev/disk/by-uuid/" + partitionUuid).c_str(), deviceBuf, 100);
	if (size == -1) { //if this didn't work, try to convert the uuid to uppercase
		for (std::string::iterator iter = partitionUuid.begin(); iter != partitionUuid.end(); iter++)
			*iter = std::toupper(*iter);
		size = readlink((this->env->cfg_dir_prefix + "/dev/disk/by-uuid/" + partitionUuid).c_str(), deviceBuf, 100);
	}
	if (size == -1) {
		return result; //abort with empty result
	}

	deviceBuf[size] = '\0';

	std::vector<std::string> regexResult = Regex::match("([^/.0-9]+)([0-9]+)$", deviceBuf);
	result.partNum = regexResult[2];

	std::string diskDevice = regexResult[1];

	SmartFileHandle handle = this->getFileHandle();

	try {
		while (result.hddNum == "") {
			std::string row = handle.getRow();
			if (row.find(diskDevice) != -1) {
				result.hddNum = Regex::match("^\\(hd([0-9]+)\\).*$", row)[1];
				break;
			}
		}
	} catch (SmartFileHandle::Exception e) {
		if (e != SmartFileHandle::END_OF_FILE) //don't throw if we didn't find the mapped value
			throw e;
	}
	handle.close();

	return result;
}