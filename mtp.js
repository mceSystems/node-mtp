var nbind = require('nbind');
const path = require("path");
var lib = nbind.init(path.resolve(__dirname, "build/Release")).lib;
var mtp = exports = module.exports = lib;

mtp.STORAGE_SORTBY_NOTSORTED = 0;
mtp.STORAGE_SORTBY_FREESPACE = 1;
mtp.STORAGE_SORTBY_MAXSPACE = 2;

mtp.FILES_AND_FOLDERS_ROOT = 0xffffffff;

mtp.FILETYPE_FOLDER = 0;
mtp.FILETYPE_WAV = 1;
mtp.FILETYPE_MP3 = 2;
mtp.FILETYPE_WMA = 3;
mtp.FILETYPE_OGG = 4;
mtp.FILETYPE_AUDIBLE = 5;
mtp.FILETYPE_MP4 = 6;
mtp.FILETYPE_UNDEF_AUDIO = 7;
mtp.FILETYPE_WMV = 8;
mtp.FILETYPE_AVI = 9;
mtp.FILETYPE_MPEG = 10;
mtp.FILETYPE_ASF = 11;
mtp.FILETYPE_QT = 12;
mtp.FILETYPE_UNDEF_VIDEO = 13;
mtp.FILETYPE_JPEG = 14;
mtp.FILETYPE_JFIF = 15;
mtp.FILETYPE_TIFF = 16;
mtp.FILETYPE_BMP = 17;
mtp.FILETYPE_GIF = 18;
mtp.FILETYPE_PICT = 19;
mtp.FILETYPE_PNG = 20;
mtp.FILETYPE_VCALENDAR1 = 21;
mtp.FILETYPE_VCALENDAR2 = 22;
mtp.FILETYPE_VCARD2 = 23;
mtp.FILETYPE_VCARD3 = 24;
mtp.FILETYPE_WINDOWSIMAGEFORMAT = 25;
mtp.FILETYPE_WINEXEC = 26;
mtp.FILETYPE_TEXT = 27;
mtp.FILETYPE_HTML = 28;
mtp.FILETYPE_FIRMWARE = 29;
mtp.FILETYPE_AAC = 30;
mtp.FILETYPE_MEDIACARD = 31;
mtp.FILETYPE_FLAC = 32;
mtp.FILETYPE_MP2 = 33;
mtp.FILETYPE_M4A = 34;
mtp.FILETYPE_DOC = 35;
mtp.FILETYPE_XML = 36;
mtp.FILETYPE_XLS = 37;
mtp.FILETYPE_PPT = 38;
mtp.FILETYPE_MHT = 39;
mtp.FILETYPE_JP2 = 40;
mtp.FILETYPE_JPX = 41;
mtp.FILETYPE_ALBUM = 42;
mtp.FILETYPE_PLAYLIST = 43;
mtp.FILETYPE_UNKNOWN = 44;