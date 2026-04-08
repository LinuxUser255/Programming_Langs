main :: IO ()
main = do
    let name = "Alice"      -- immutable binding
        age = 30 :: Int
        pi = 3.14159 :: Double
    putStrLn $ "Name: " ++ name ++ ", Age: " ++ show age
