load r1 30 ; compare
load r2 1 ; const increment
load r3 0 ; increment
load r4 0 ; result
goto cls

cls:
	cmp r1 r4
	goto end if ==
	add r2 r3 r4
	load r3 r4
	putchar \n
	goto cls

end:
end