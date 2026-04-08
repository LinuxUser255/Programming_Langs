# C# Basics

dotnet new console -o . (first time) then:
dotnet run --project .
or simply: csc Program.cs && ./Program.exe (if using old compiler)

``bash
csc 04_loops.cs && ./04_loops.exe

# or with dotnet (recommended):
dotnet new console -o temp && cp 04_loops.cs temp/Program.cs && dotnet run --project temp
```
