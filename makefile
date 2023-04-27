



cfg:
	xmake f  -m debug
	xmake project -k compile_commands

macros:
	xmake m --begin
	xmake b test
	xmake run test
	xmake m --end t

