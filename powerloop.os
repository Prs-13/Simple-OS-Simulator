load r1 1 ; compare
load r2 1
load r3 getint ; base
load r4 getint ; power
load r5 r3
goto loop

loop:
	mul r3 r5 r6
	load r3 r6
	add r1 r2 r7
	load r1 r7
	cmp r1 r4
	goto loop if <
	goto end if ==
end:
	print R3
	end