import sys
import os
def dirNavigate( path, level, curLevel ):
    os.chdir( path )
    curLevel = curLevel + 1
    level = level - 1
    files = os.listdir( path )
    for file in files:
        abspath = os.path.abspath(file)
        isDir = os.path.isdir( abspath )
        if isDir:
            printName( file, True, curLevel)
            if level != 0:
                dirNavigate( abspath, level, curLevel )
                os.chdir(path)
        else:
            printName( file, False, curLevel)

def printName( name, isdir, curLevel ):
    idx = 0;
    while( idx < curLevel ):
        print('    ', end='', file=log)
        idx = idx + 1

    if isdir:
        print('- ', end='', file=log )
    print(name, file=log )


if len(sys.argv) != 3:
    print( "pls specify the dir you want to navigate!")
    exit()

path = sys.argv[1]
level = int(sys.argv[2])
print( 'navigate path: ', path )

log = open( 'dirNavigator.txt', 'w' )
print( path, file=log)
dirNavigate( path, level, 0 )
log.close()
