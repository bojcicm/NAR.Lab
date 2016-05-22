using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Vjezba3
{
    class Program
    {
        static void Main(string[] args)
        {
            var linesToWrite = new List<string>();
            
            linesToWrite.AddRange(Example1Run());
            linesToWrite.Add("");

            linesToWrite.AddRange(Example3Run());
            linesToWrite.Add("");

            linesToWrite.AddRange(Example4Run());

            linesToWrite.Add("");
            linesToWrite.AddRange(Example5Run());

            System.IO.File.WriteAllLines(@"C:\Users\mbojcic\Documents\Visual Studio 2015\Projects\NAR.Lab\Vjezba3\test.txt", linesToWrite);
        }

        public static List<string> Example1Run()
        {
            var lines = new List<string> {"Example 1 and 2"};
            var sw = Stopwatch.StartNew();

            for (var i = 2; i < 4097*4; i*=2)
            {
                lines.Add($"Step size = {i}");
                Console.WriteLine($"Example 1 - step size = {i}");
                sw.Restart();
                Example1(i);
                lines.Add($"Time elapsed: {sw.ElapsedMilliseconds} ms");
                Console.WriteLine($"Time elapsed: {sw.ElapsedMilliseconds} ms");

            }

            sw.Reset();
            lines.Add("End of example 1 and 2");
            return lines;
        }

        public static List<string> Example3Run()
        {
            var lines = new List<string> { "Example 3" };
            var sw = Stopwatch.StartNew();

            for (var i = 2; i < 960000; i *= 2)
            {
                lines.Add($"Array size = {i* 256 / 1024} kiloBytes");
                Console.WriteLine($"Array size = {i * 256 / 1024} kiloBytes");
                sw.Restart();
                Example3(i*256);
                lines.Add($"Time elapsed: {sw.ElapsedMilliseconds} ms");
                Console.WriteLine($"Time elapsed: {sw.ElapsedMilliseconds} ms\n");

            }

            sw.Reset();
            lines.Add("End of example 3");
            return lines;
        }

        public static List<string> Example4Run()
        {
            var lines = new List<string> { "Example 4" };
            var sw = Stopwatch.StartNew();

            for (var i = 2; i < 960000; i *= 2)
            {
                lines.Add($"Array size = {i * 256 / 1024} kiloBytes");
                Console.WriteLine($"Array size = {i * 256 / 1024} kiloBytes");
                sw.Restart();
                Example4(i * 256, false);
                lines.Add($"First pass time elapsed: {sw.ElapsedMilliseconds} ms");
                Console.WriteLine($"First pass time elapsed: {sw.ElapsedMilliseconds} ms");
                sw.Restart();
                Example4(i * 256, true);
                lines.Add($"Second pass time elapsed: {sw.ElapsedMilliseconds} ms");
                Console.WriteLine($"Second pass time elapsed: {sw.ElapsedMilliseconds} ms\n");

            }

            sw.Reset();
            lines.Add("End of example 4");
            return lines;
        }

        public static List<string> Example5Run()
        {
            var lines = new List<string> { "Example 3" };
            var sw = Stopwatch.StartNew();

            for (var i = 2; i < 1025; i*=2)
            {
                lines.Add($"Step size = {i}");
                Console.WriteLine($"Step size = {i}");
                sw.Restart();
                Example5(i);
                lines.Add($"Time elapsed: {sw.ElapsedMilliseconds} ms");
                Console.WriteLine($"Time elapsed: {sw.ElapsedMilliseconds} ms\n");

            }

            sw.Reset();
            lines.Add("End of example 5");
            return lines;
        } 

        public static void Example1(int step)
        {
            var arr = new int[64*1024*1024];
            var arrLength = arr.Length;
            for (int i = 0; i < arrLength; i+=step)
            {
                arr[i] *= 3;
            }
        }

        public static void Example3(int size)
        {
            var steps = 64*1024*1024;
            
            var arr = new int[size];
            int lenghtMod = arr.Length - 1;

            for (int i = 0; i < steps; i++)
            {
                arr[(i*16) & lenghtMod] ++;
            }
        }

        public static void Example4(int size, bool a)
        {
            var steps = 64 * 1024 * 1024;

            var arr = new int[size];
            int lenghtMod = arr.Length;
            if (a)
            {
                for (int i = 0; i < lenghtMod; i++)
                {
                    arr[i]++;
                    arr[i]++;
                }
            }
            else
            {
                for (int i = 1; i < lenghtMod; i++)
                {
                    arr[i-1]++;
                    arr[i]++;
                }
            }
        }

        public static void Example5(int step)
        {
            var arr = new int[1048576];
            var lenghtMod = arr.Length;

            var p = 0;
            for (var i = 0; i < lenghtMod; i++)
            {
                if (p >= lenghtMod) p = 0;
                arr[p]++;
                p += step;
            }
        }

    }
}
