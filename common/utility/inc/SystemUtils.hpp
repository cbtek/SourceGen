


    #else  
        ssize_t len = ::readlink("/proc/self/exe", buffer, sizeof(buffer)-1);