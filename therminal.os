set \n y
start:
    set getchar x
    cmp x y
    goto compare if ==
    set x buffer
    goto start

compare: ; ----- check which command -----
    cmp buffer help
    goto help_cmd if ==

    cmp buffer run
    goto run_cmd if ==

    cmp buffer cls
    goto cls_cmd if ==

    cmp buffer mkdir
    goto mkdir_cmd if ==

    cmp buffer touch
    goto touch_cmd if ==

    cmp buffer write
    goto write_cmd if ==

    cmp buffer exit
    goto exit_cmd if ==

    goto start
    
help_cmd: ; ----- HELP -----
    runcmd help
    goto start

run_cmd: ; ----- RUN -----
    runcmd run
    goto start

cls_cmd: ; ----- CLS -----
    runcmd cls
    goto start

mkdir_cmd: ; ----- MKDIR -----
    runcmd mkdir
    goto start

touch_cmd: ; ----- TOUCH -----
    runcmd touch
    goto start

write_cmd: ; ----- WRITE -----
    runcmd write
    goto start

exit_cmd: ; ----- EXIT -----
    runcmd exit
    goto start ; if failed to run cmd