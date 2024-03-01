#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<stdlib.h>
#include<ctime>
#include<QMessageBox>
#include<algorithm>
#include<vector>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ArraySize=0;
    linearSearch=false;
    binarySearch=false;
    SortTime=0;
    Sorted=false;
    SearchTime=0;
    ArrayGenerated=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DisplayArray()
{
    ui->ArrayLab->setText("");
    for(int i=0;i<ArraySize;i++)
    {
        ui->ArrayLab->setText(ui->ArrayLab->text()+'\n'+Arr[i]);
    }
}



void MainWindow::on_GenerateBut_clicked()
{
    if(!ui->ArraySizeEdit->text().isEmpty())
    {
        ArraySize=ui->ArraySizeEdit->text().toInt();
        if(ArraySize==1)
        {
            Sorted=true;
            ui->ArrayConditionLab->setText("Sorted Array");
        }
        else
        {
            Sorted=false;
            ui->ArrayConditionLab->setText("Unsorted Array");
        }
        linearSearch=false;
        binarySearch=false;
        Arr=new QString[ArraySize];
        srand(time(0));
        for(int i=0;i<ArraySize;i++)
        {
            Arr[i]=QString::number(rand()%ArraySize);
        }
        DisplayArray();
        ui->InfoLab->setText("Array Size is : "+QString::number(ArraySize));
        ArrayGenerated=true;
        ui->ErrorsLab->setText("");
    }
    else
    {
        ui->ErrorsLab->setText("Please enter the array size!!");
    }
}


void MainWindow::on_LinearSearchBut_clicked()
{
    if(ArrayGenerated)
    {
        binarySearch=false;
        linearSearch=true;
        ui->ErrorsLab->setText("");
    }
    else
    {
        ui->ErrorsLab->setText("You have to generate an array first!!");
    }
}


void MainWindow::on_BinarySearchBut_clicked()
{
    if(ArrayGenerated)
    {
        linearSearch=false;
        if(Sorted)
        {
            binarySearch=true;
            ui->ErrorsLab->setText("");
        }
        else
        {
            ui->ErrorsLab->setText("Array must be sorted before\n performing binary search!!");
        }
    }
    else
    {
        ui->ErrorsLab->setText("You have to generate an array first!!");
    }
}

int MainWindow::LinearSearch(int Num)
{
    for(int i=0;i<ArraySize;i++)
    {
        if(Num==Arr[i].toInt())
        {
            return i;
        }
    }
    return -1;
}

int MainWindow::BinarySearch(int Num)
{
    int Low=0,High=ArraySize-1;
    while(Low<=High)
    {
        int Mid = Low + (High - Low) / 2;
        if(Arr[Mid].toInt()==Num)
        {
            return Mid;
        }
        else if (Arr[Mid].toInt() < Num)
        {
            Low = Mid + 1;
        }
        else
        {
            High = Mid - 1;
        }
    }
    return -1;
}

void MainWindow::mergeSort(int left,int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, mid, right);
    }
}


void MainWindow::on_FindBut_clicked()
{
    if(ArrayGenerated)
    {
        if(!ui->FindLineEdit->text().isEmpty())
        {
            this->SearchTime=0;
            int Target=ui->FindLineEdit->text().toInt();
            int Index=-2;
            if(linearSearch)
            {
                std::chrono::steady_clock::time_point now=std::chrono::steady_clock::now();
                Index=LinearSearch(Target);
                std::chrono::steady_clock::time_point then=std::chrono::steady_clock::now();
                this->SearchTime=std::chrono::duration_cast<std::chrono::nanoseconds>(then-now).count();
                ui->ErrorsLab->setText("");
                ui->InfoLab->setText(ui->InfoLab->text()+"\nSearching using Linear Search...");
            }
            else if(binarySearch)
            {
                std::chrono::steady_clock::time_point now=std::chrono::steady_clock::now();
                Index=BinarySearch(Target);
                std::chrono::steady_clock::time_point then=std::chrono::steady_clock::now();
                this->SearchTime=std::chrono::duration_cast<std::chrono::nanoseconds>(then-now).count();
                ui->ErrorsLab->setText("");
                 ui->InfoLab->setText(ui->InfoLab->text()+"\nSearching using Binary Search...");
            }
            else
            {
                ui->ErrorsLab->setText("Please Choose a Searching Criteria!!");
            }
            if(Index!=-2)
            {
                QMessageBox Msg;
                Msg.setWindowTitle("Message Box");
                if(Index==-1)
                {
                    Msg.setText("Item was not found in the array\n");
                }
                else
                {
                    Msg.setText("Item was found in the array at index : "+QString::number(Index)+'\n');
                }
                Msg.setText(Msg.text()+"Time in nanoseconds needed to find it : "+QString::number(SearchTime)+'\n');
                Msg.setText(Msg.text()+"Time in nanoseconds needed to sort the array : "+QString::number(SortTime));
                Msg.setIcon(QMessageBox::Information);
                Msg.setStandardButtons(QMessageBox::Ok);
                Msg.exec();
            }
        }
        else
        {
            ui->ErrorsLab->setText("Please enter a number to \nsearch for in the array!!");
        }
    }
    else
    {
        ui->ErrorsLab->setText("You have to generate an array first!!");
    }
}

void MainWindow::merge(int left, int mid, int right)
{
    int i, j, k;
        int n1 = mid - left + 1;
        int n2 = right - mid;

        int L[n1], R[n2];

        for (i = 0; i < n1; i++)
            L[i] = Arr[left + i].toInt();
        for (j = 0; j < n2; j++)
            R[j] = Arr[mid + 1 + j].toInt();

        i = 0;
        j = 0;
        k = left;

        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                Arr[k] = QString::number(L[i]);
                i++;
            }
            else {
                Arr[k] = QString::number(R[j]);
                j++;
            }
            k++;
        }

        while (i < n1) {
            Arr[k] = QString::number(L[i]);
            i++;
            k++;
        }

        while (j < n2) {
            Arr[k] = QString::number(R[j]);
            j++;
            k++;
        }
}


void MainWindow::on_MergeSortBut_clicked()
{
    if(!ArrayGenerated)
    {
        ui->ErrorsLab->setText("You have to generate an array first!!");
    }
    else if(Sorted)
    {
        ui->ErrorsLab->setText("Array is already sorted!!");
    }
    else
    {
        this->SortTime=0;
        std::chrono::steady_clock::time_point now=std::chrono::steady_clock::now();
        mergeSort(0,ArraySize-1);
        std::chrono::steady_clock::time_point then=std::chrono::steady_clock::now();
        this->SortTime=std::chrono::duration_cast<std::chrono::nanoseconds>(then-now).count();
        DisplayArray();
        ui->InfoLab->setText(ui->InfoLab->text()+'\n'+"Sorting Using MergeSort...");
        Sorted=true;
        ui->ArrayConditionLab->setText("Sorted Array");
        ui->ErrorsLab->setText("");
    }
}





void MainWindow::on_STLSortBut_clicked()
{
    if(!ArrayGenerated)
    {
        ui->ErrorsLab->setText("You have to generate an array first!!");
    }
    else if(Sorted)
    {
        ui->ErrorsLab->setText("Array is already sorted!!");
    }
    else
    {
        ui->ArrayConditionLab->setText("Sorted Array");
        ui->InfoLab->setText(ui->InfoLab->text()+'\n'+"Sorting Using STL Sort...");
        std::vector<int> V;
        for(int i=0;i<ArraySize;i++)
        {
            V.push_back(Arr[i].toInt());
        }
        this->SortTime=0;
        std::chrono::steady_clock::time_point now=std::chrono::steady_clock::now();
        std::sort(V.begin(),V.end());
        std::chrono::steady_clock::time_point then=std::chrono::steady_clock::now();
        this->SortTime=std::chrono::duration_cast<std::chrono::nanoseconds>(then-now).count();
        for(int i=0;i<ArraySize;i++)
        {
            Arr[i]=QString::number(V[i]);
        }
        DisplayArray();
        Sorted=true;
        ui->ErrorsLab->setText("");
    }
}

