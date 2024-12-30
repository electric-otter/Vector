    try: 
        with open(filename, "vectorcode") as outfile: 
            outfile.write('Launch vectorcode file...') 
     
     
    except IOError: 
        print ( 'Cannot open vectorcode!' ) 
     
    else: 
        print(('successful write to ' + filename)); 
