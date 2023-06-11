
#pragma once
#ifndef __calculator_H__
#define __calculator_H__

#include <QtWidgets/QMainWindow>
#include <cstdint>
#include <QKeyEvent>
#include <queue>

static short error_flag{};
void error_thrown(double &x);

namespace Ui {
class Calculator;
}

struct Calc
{
       double  num{};

     double operator+(const Calc& other) const
    {
           double res{};
         try
         {
             res = num + other.num;
             if (res > UINT64_MAX  || res < INT64_MIN)
             {
                 error_flag++;
                 throw res;
             }
             else
                 return res;
         }
         catch (double& x)
         {
             if (error_flag == 1)
             {
                 error_thrown(x);
             }
             else
                 error_flag = 0;
         }
         return 0;
    }
      double  operator-(const Calc& other) const
    {
          double res{};
          try
          {
              res = num - other.num;

              if (res > UINT64_MAX || res < INT64_MIN)
              {
                  error_flag++;
                  throw res;
              }
              else
                  return res;
          }
          catch (double& x)
          {
              if (error_flag == 1)
              {
                  error_thrown(x);
              }
              else
                  error_flag = 0;
          }
          return 0;
    }

      double  operator*(const Calc& other) const
    {
          double res{};
          try
          {
              res = num * other.num;

              if (res > UINT64_MAX || res < INT64_MIN)
              {
                  error_flag++;
                  throw res;
              }
              else
                  return res;
          }
          catch (double& x)
          {
              if (error_flag == 1)
              {
                  error_thrown(x);
              }
              else
                  error_flag = 0;
          }
          return 0;
    }

      double  operator/(const Calc& other) const
    {
          double res{};
          try
          {
              res = num / other.num;

              if (res > UINT64_MAX || res < INT64_MIN)
              {
                  error_flag++;
                  throw res;
              }
              else
                  return res;
          }
          catch (double& x)
          {
              if (error_flag == 1)
              {
                  error_thrown(x);
              }
              else
                  error_flag = 0;
          }
          return 0;
    }

      double  operator^(const Calc& other) const
      {
           double res{};

          try
          {
              res = pow(num, other.num);

              if (res > UINT64_MAX || res < INT64_MIN)
              {
                  error_flag++;
                  throw res;
              }
              else
                  return res;
          }
          catch (double &x)
          {
              if (error_flag == 1)
              {
                  error_thrown(x);
              }else
                  error_flag = 0;
          }
          return 0;
      }

      double  operator%(const Calc& other) const
    {
           double res{};
          try
          {
              res = fmod(num, other.num);
              if (res > UINT64_MAX || res < INT64_MIN)
              {
                  error_flag++;
                  throw res;
              }
              else
                  return res;
          }
          catch (double& x)
          {
              if (error_flag == 1)
              {
                  error_thrown(x);
              }
              else
                  error_flag = 0;
          }
          return 0;
    }
};

class KeyClass : public QWidget
{
    Q_OBJECT

public:
    explicit KeyClass(QWidget* parent = 0) :QWidget(parent) {}

    virtual void keyPressEvent(QKeyEvent* event) = 0;

    KeyClass() = default;
};


class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget* parent = nullptr);
    ~Calculator();

public:
    bool is_zero();
    bool is_doted();
    void filter();
    void result(char _operator);
    char get_op();
    void coma_seperator();
    void keyPressEvent(QKeyEvent* event) override;
    void resizeEvent(QResizeEvent*) override;

private slots:
    void on_Button_zero_clicked();
    void on_Button_one_clicked();
    void on_Button_tow_clicked();
    void on_Button_three_clicked();
    void on_Button_four_clicked();
    void on_Button_five_clicked();
    void on_Button_six_clicked();
    void on_Button_seven_clicked();
    void on_Button_eight_clicked();
    void on_Button_nine_clicked();
    void on_Button_ecual_clicked();
    void on_Button_dot_clicked();
    void on_Button_delete_clicked();
    void on_Button_controler_clicked();
    void on_Button_plus_clicked();
    void on_Button_minus_clicked();
    void on_Button_divided_clicked();
    void on_Button_pow_clicked();
    void on_Button_mod_clicked();
    void on_Button_multiply_clicked();
    void on_Button_clear_clicked();
    void on_comma_counter_clicked();
    void on_comma_cleaner_clicked();
    void on_result_screen_textEdited();
    void on_Button_minus_plus_clicked();
    void on_Button_exit_clicked();
    void on_actionOn_Top_triggered();
    void on_History_clicked();
    void on_History_Item_clicked();

private:
    Ui::Calculator *ui;
    Calc op;
    Calc t;
};




#endif // !__calculator_H__
