#pragma once
#include <iostream>
#include <string>
#include <vector>

template<typename T> // ����� ���������
void OutPut(T arg) {  
    std::cout << arg << " ";
}



template<typename T> // ����� �������
void OutPut(std::vector <T> arg) {
    for (auto i : arg) {
        std::cout << i << " ";
    }
}



int SequenceLength(int n); // ���������� ����� ������������������



char inversation(char a); // ���������� char a


bool inversation(bool a);// ���������� ��� bool


void ZerosOnesSequence (std::string& str, int n); // ������� ��������� ������������������


int NumberOfOnesBinaryNotation(int n); // ����������� ���������� 1 � �������� �������������


int DigitMod2(int a); // ������ �� ������� �� 2


void ZerosOnesSequenceMod2(std::vector<int>& nums, int v); // ������� ���������� ������������������


bool IsEqual(std::string str, std::vector <int> files); //��������t ���� �������������������
