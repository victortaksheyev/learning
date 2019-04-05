using System;

class ReadFromFile
{
    // takes a word and returns its initial

    static void Main()
    {   
        Console.WriteLine("Enter base number: ");
        int baseNum = Convert.ToInt32(Console.ReadLine());
        // Console.WriteLine("The number you entered: {0}", baseNum);
        Console.Write("Enter exponent: ");
        int exp = Convert.ToInt32(Console.ReadLine());
        Console.WriteLine(exponent(baseNum, exp));
    }

    static int exponent(int baseNum, int powNum) {
        int result = 1;
        if (powNum == 0) return 1;
        // if (powNum == 1) return baseNum;
        for (int i = 0; i < powNum; i++) {
            result *= baseNum;           // 3 ^ 2 means 3*3
        }
        return result;
    }
}
