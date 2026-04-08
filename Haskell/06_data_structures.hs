main :: IO ()
main = do
    let numbers = [1,2,3,4,5]
        person = [("name", "John"), ("age", "28")]
        unique = [1,2,2,3]          -- list, duplicates kept
    print numbers
    print $ lookup "name" person
