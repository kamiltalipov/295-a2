#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

int n;
int Answer = 0;

int Bubble_Sort(vector <int> &Array)
{
	int Answer = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (Array[j] > Array[i])
			{
				swap(Array[i], Array[j]);
				Answer++;
			}
		}
	}
	return Answer;
}

void Merge(int Left, int Right, vector <int> &Main_Array)
{
	int Middle = (Left + Right) / 2;
	int Left_Pos = Left, Tmp_Pos = 0, Right_Pos = Middle + 1;
	vector <int> Temp(Right - Left + 1);
	while ((Left_Pos <= Middle) && (Right_Pos <= Right))
	{
		if (Main_Array[Left_Pos] <= Main_Array[Right_Pos])
		{
			Temp[Tmp_Pos] = Main_Array[Left_Pos];
			Left_Pos++;
			Tmp_Pos++;
		}
		else
		{
			Temp[Tmp_Pos] = Main_Array[Right_Pos];
			Right_Pos++;
			Tmp_Pos++;
			Answer += Middle - Left_Pos + 1;
		}	
	}
	
	while (Left_Pos <= Middle)
	{
			Temp[Tmp_Pos] = Main_Array[Left_Pos];
			Left_Pos++;
			Tmp_Pos++;
	}
	
	while (Right_Pos <= Right)
	{
			Temp[Tmp_Pos] = Main_Array[Right_Pos];
			Right_Pos++;
			Tmp_Pos++;
	}
	
	for (int i = 0; i < Tmp_Pos; i++)
	{
		Main_Array[Left + i] = Temp[i];
	}
}

void Merge_Sort(int Left, int Right, vector <int> &Main_Array)
{
	int Middle = (Left + Right) / 2;
	if (Left < Right)
	{
		Merge_Sort(Left, Middle, Main_Array);
		Merge_Sort(Middle + 1, Right, Main_Array);
		Merge(Left, Right, Main_Array);
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	cin >> n;
	
	vector <int> Main_Array(n), Copied_Array(n);
	
	for (int i = 0; i < n; i++)
	{
		cin >> Main_Array[i];
		Copied_Array[i] = Main_Array[i];
	}
		
	Merge_Sort(0, n - 1, Main_Array);
	cout << Answer << endl;
	cout << Bubble_Sort(Copied_Array) << endl;
		
	fclose(stdin);
	fclose(stdout);
	return 0;
}
