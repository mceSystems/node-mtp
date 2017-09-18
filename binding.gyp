{
	"targets": [
		{
			"includes": [
				"auto.gypi"
			],
			"sources": [
				"src\\node-mtp.cc"
			],
			"include_dirs+": [
				"libmtp.mpd\\src"
			],
			"libraries": [ 
				"..\\libmtp.mpd\\src\\.libs\\libmtp.dll.a" 
			]
		}
	],
	"includes": [
		"auto-top.gypi"
	]
}
