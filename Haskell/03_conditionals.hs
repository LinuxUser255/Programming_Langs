main :: IO ()
main = do
    let age = 20
    putStrLn $ if age < 18 then "Minor"
               else if age < 65 then "Adult"
               else "Senior"
