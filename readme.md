classes:
    photo
        name
        int** pxls
        int height
        int weight
        pure virt functions*

        grayscale
        monochrome
        rotate <direction>
        negative

        children PGM, PPM, PBM
            format - p1,p2,p3

    session
        id, photo*, string* (functions)

        undo
        add <image>
        session info
        collage <direction> <image1> <image2> <outimage>
        
    command
        open
        load
        close
        save
        saveas
        help
        exit        

    UI
        sesion*
        curr session index
        
        switch <session id>
        console output

Notes:
    PPM -> PGM red+ / 3
    PPM -> PBM red+ / 3 > 128
    PGM -> PBM > 128