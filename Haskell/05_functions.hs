greet :: String -> Int -> String
greet name age = "Hello " ++ name ++ ", you are " ++ show age ++ " years old."

main :: IO ()
main = do
    putStrLn $ greet "Bob" 25
    putStrLn $ greet "Alice" 32
