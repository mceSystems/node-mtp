#include <string>
#include <iostream>
#include <vector>
#ifdef _WIN32
#include <WinSock2.h>
#endif

#include "nbind/nbind.h"
#include "libmtp.h"

typedef LIBMTP_raw_device_t raw_device_t;

class file_t{
public:
	file_t(LIBMTP_file_t* file = nullptr) : m_name(file?file->filename:""){
		if (file){
			memcpy(&m_file, file, sizeof(m_file));
		}else{
			memset(&m_file, 0, sizeof(m_file));
		}
		m_file.filename = (char*)m_name.c_str();
	}
	explicit file_t(const file_t* file) : m_file(file->m_file),m_name(file->m_name){
		m_file.filename = (char*)m_name.c_str();
	}
	
	std::string getName(){return m_name;}
	void setName(const std::string name){m_name = name;}

	uint32_t getId(){return m_file.item_id;}
	void setId(const uint32_t id){m_file.item_id = id;}

	uint32_t getType(){return m_file.filetype;}
	void setType(const uint32_t type){m_file.filetype = (LIBMTP_filetype_t)type;}

	uint64_t getSize(){return m_file.filesize;}
	void setSize(const uint64_t size){m_file.filesize = size;}

	uint32_t getParentId(){return m_file.parent_id;}
	void setParentId(const uint32_t parentId){m_file.parent_id = parentId;}
	
	uint32_t getStorageId(){return m_file.storage_id;}
	void setStorageId(const uint32_t storageId){m_file.storage_id = storageId;}

	LIBMTP_file_t* get(){return &m_file;}

private:
	LIBMTP_file_t m_file;
	std::string m_name;
};

class devicestorage_t{
public:
	devicestorage_t(LIBMTP_devicestorage_t* storage=nullptr) : m_storage(*storage),m_description(storage->StorageDescription){}
	explicit devicestorage_t(const devicestorage_t* storage) : m_storage(storage->m_storage),m_description(storage->m_description){};
	
	uint32_t getId(){return m_storage.id;}
	void setId(const uint32_t id){m_storage.id = id;}

	std::string getDescription(){return m_description;}
	void setDescription(const std::string description){m_description = description;}

private:
	LIBMTP_devicestorage_t m_storage;
	std::string m_description;
};

class mtpdevice_t
{
public:
	mtpdevice_t(LIBMTP_mtpdevice_t* device=nullptr) : m_device(device){}
	explicit mtpdevice_t(const mtpdevice_t* device) : m_device(device->m_device){}
	LIBMTP_mtpdevice_t* m_device;
	std::vector<devicestorage_t> getStorages(){
		std::vector<devicestorage_t> result;
		for (LIBMTP_devicestorage_t* storage = m_device->storage; storage != nullptr; storage = storage->next) {
			result.push_back(devicestorage_t(storage));
		}
		return result;
	}
};


int FileProgressCallback (uint64_t const sent, uint64_t const total, void const * const data)
{
	nbind::cbFunction cb = *((nbind::cbFunction*)data);
	cb(sent, total);
	return 0;
}

int Get_File_To_File(mtpdevice_t device, uint32_t const id,	const std::string path, nbind::cbFunction& cb)
{
	return LIBMTP_Get_File_To_File(device.m_device, id, path.c_str(), FileProgressCallback, (const void*)&cb);
}

int Send_File_From_File(mtpdevice_t device,	const std::string path, file_t filedata, nbind::cbFunction& cb)
{
	return LIBMTP_Send_File_From_File(device.m_device, path.c_str(), filedata.get(), FileProgressCallback, (const void*)&cb);
}

std::vector<file_t> Get_Files_And_Folders(mtpdevice_t device, uint32_t const storage, uint32_t const parent)
{
	std::vector<file_t> result;
	LIBMTP_file_t* next = nullptr;

	for (LIBMTP_file_t* file = LIBMTP_Get_Files_And_Folders(device.m_device, storage, parent); nullptr != file; file = next)
	{
		result.push_back(file);
		next = file->next;
		LIBMTP_destroy_file_t(file);
	}

	return result;
}

int Get_Storage(mtpdevice_t device, const int sortby)
{
	return LIBMTP_Get_Storage(device.m_device, sortby);
}

std::string Get_Friendlyname(mtpdevice_t device)
{
	char* fn = LIBMTP_Get_Friendlyname(device.m_device);
	std::string result(fn);
	//free(fn)
	return result;
}

void Release_Device(mtpdevice_t device)
{
	LIBMTP_Release_Device(device.m_device);
}

mtpdevice_t Open_Raw_Device_Uncached(raw_device_t rawDevice)
{
	return mtpdevice_t(LIBMTP_Open_Raw_Device_Uncached(&rawDevice));
}

mtpdevice_t Open_Raw_Device(raw_device_t rawDevice)
{
	return mtpdevice_t(LIBMTP_Open_Raw_Device(&rawDevice));
}

void Detect_Raw_Devices(nbind::cbFunction& cb)
{
	LIBMTP_raw_device_t * rawdevices = nullptr;
	int numrawdevices = 0;
	
	LIBMTP_error_number_t err = LIBMTP_Detect_Raw_Devices(&rawdevices, &numrawdevices);
	std::vector<raw_device_t> result;
	
	if (nullptr != rawdevices){
		for (int i = 0; i < numrawdevices; i++) {
			result.push_back(rawdevices[i]);
		}
		//free(rawdevices);
	}
	
	cb((int)err, result);
}

void Init()
{
	LIBMTP_Init();
}

#include "nbind/nbind.h"

NBIND_CLASS(file_t){
	construct<>();
	construct<const file_t*>();
	getset(getName,setName);
	getset(getId,setId);
	getset(getType,setType);
	getset(getSize,setSize);
	getset(getParentId,setParentId);
	getset(getStorageId,setStorageId);
}

NBIND_CLASS(mtpdevice_t){
	construct<>();
	construct<const mtpdevice_t*>();
	method(getStorages);
}

NBIND_CLASS(devicestorage_t){
	construct<>();
	construct<const devicestorage_t*>();
	getset(getId,setId);
	getset(getDescription,setDescription);
}

NBIND_CLASS(raw_device_t){
}

NBIND_GLOBAL() {
	function(Init);
	function(Detect_Raw_Devices);
	function(Open_Raw_Device);
	function(Open_Raw_Device_Uncached);
	function(Release_Device);
	function(Get_Friendlyname);
	function(Get_Storage);
	function(Get_Files_And_Folders);
	function(Get_File_To_File);
	function(Send_File_From_File);
  }
