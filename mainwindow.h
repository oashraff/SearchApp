#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void DisplayArray();

private slots:
    void on_GenerateBut_clicked();

    void on_LinearSearchBut_clicked();

    void on_BinarySearchBut_clicked();
    int LinearSearch(int Num);
    int BinarySearch(int Num);
    void mergeSort(int p,int r);
    void on_FindBut_clicked();
    void merge(int p,int q,int r);

    void on_MergeSortBut_clicked();


    void on_STLSortBut_clicked();

private:
    Ui::MainWindow *ui;
    int ArraySize;
    QString *Arr;
    bool linearSearch;
    bool binarySearch;
    int SortTime;
    int SearchTime;
    bool Sorted;
    bool ArrayGenerated;
};
#endif // MAINWINDOW_H
