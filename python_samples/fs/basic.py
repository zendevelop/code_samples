import os

print( os.getcwd() )

the_file = open( 'sketch.txt' )
# do the operation
for line in the_file:
    print( line, end='' )
print('\n')

the_file.seek(0)
print( 'split usage:')
for each_line in the_file:
    (role, line_spoken) = each_line.split(":")
    print( role +  ' said: ' + line_spoken, end='' )
print('\n')
    
the_file.close()