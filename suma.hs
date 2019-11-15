import Data.List
import System.IO 

add :: Int -> Int -> Int
add x y = x + y

mul :: Int -> Int -> Int
mul x y = x * y

generic :: (Int -> Int -> Int) -> [Int] -> Int -> Int
generic modi [] num = num
generic modi (x:xs) num = modi x (generic modi xs num)

espo :: Int -> Int -> Int
espo x 0 = 1
espo x 1 = x
espo x n = x * espo x (n-1)

tam :: [Int] -> Int -> Int
tam [] count = count
tam (x:xs) count = tam xs (count+1) 

l = [0,2..10]

main = do
    
    let thing = tam l 0 
    print thing
