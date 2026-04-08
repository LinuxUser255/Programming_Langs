data Person = Person { name :: String, age :: Int } deriving Show

introduce :: Person -> String
introduce p = "Hi, I'm " ++ name p ++ " and I'm " ++ show (age p) ++ " years old."

main :: IO ()
main = putStrLn $ introduce (Person "Emma" 27)
