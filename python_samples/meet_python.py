movies = ["the Holy Grail", "The Life of Brain", "The Meaning of Life"];
movies.insert( 1, 1975)
movies.insert( 3, 1979)
movies.append(1983)

print( movies )

def print_lol( the_list ):
''' function description here'''
    fo each_item in the_list:
        if isinstance( each_item, list)
            print_lol( each_item )
        else:
            print( each_item )
