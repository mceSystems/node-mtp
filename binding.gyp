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
						"src/inc"
					],
					"libraries": [ 
						"../src/lib/libmtp-9.lib" 
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
