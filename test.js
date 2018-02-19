const mtp=require("./mtp");
const fs = require("fs"); 

function sendFile(device){
    const stats = fs.statSync("c:/downloads.zip");
    
    var file = new mtp.file_t();
    file.size = stats.size;
    file.name = "1.zip"
    file.type = mtp.FILETYPE_UNKNOWN;
    file.parentId = mtp.FILES_AND_FOLDERS_ROOT;
    file.storageId = 0;
    
    const r = mtp.Send_File_From_File(device, "c:/downloads.zip", file, function(sent,total){
        process.stdout.write("get file: " + sent + " of " + total + "\r");
    });
    console.log("");
    console.log("send file returned ", r);
}

function fileTree(device, storageId, folderId, indent){
    const files = mtp.Get_Files_And_Folders(device, storageId, folderId);
    files.forEach(function(file){
        console.log(indent, file.name);
        if (mtp.FILETYPE_FOLDER == file.type){
            fileTree(device, storageId, file.id, indent + " ");
        }
        if ("1.zip" == file.name){
            // const r = mtp.Get_File_To_File(device, file.id, "1.zip", function(sent,total){
            //     process.stdout.write("get file: " + sent + " of " + total + "\r");
            // });
            console.log(file.id);
            console.log("");
            console.log("get file returned ", r);
        }
    });
}

mtp.Init();
mtp.Detect_Raw_Devices(function(err, rawDevices){
    rawDevices.forEach(function(rawDevice) {
        const device = mtp.Open_Raw_Device_Uncached(rawDevice);        
        console.log("Friendly Name: ", mtp.Get_Friendlyname(device));
        console.log("Model Name: ", mtp.Get_Modelname(device));
        console.log("Serial: ", mtp.Get_Serialnumber(device));
        console.log("version: ", mtp.Get_Deviceversion(device));
        
        //  mtp.Get_Storage(device, mtp.STORAGE_SORTBY_NOTSORTED);
        //  device.getStorages().forEach(function(storage){
        //      console.log("storage: ", storage.description);
        //      fileTree(device, storage.id, mtp.FILES_AND_FOLDERS_ROOT, "");
        //  });
        
        // //sendFile(device);

        // mtp.Get_File_To_File(device, 2000014, "1.zip", function(sent,total){
        //          process.stdout.write("get file: " + sent + " of " + total + "\r");
        // });

        mtp.Release_Device(device);
    }, this);
})

console.log("====================================");
console.log("done");