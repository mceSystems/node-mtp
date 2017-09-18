{
	"targets": [
		{
			"includes": [
				"auto.gypi"
			],
			"sources": [
				"src/node-mtp.cc"
			],
			"conditions" : [
				['OS=="win"', {
					"include_dirs+": [
						"libmtp.mpd/src"
					],
					"libraries": [ 
						"../libmtp.mpd/src/.libs/libmtp.dll.a" 
					]
				}],
				['OS!="win"', {
					"libraries": [
						"<!@(pkg-config libmtp --libs)"
                    ]
				}]
			]
		}
	],
	"includes": [
		"auto-top.gypi"
	]
}
