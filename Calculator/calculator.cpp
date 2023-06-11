
#include "calculator.h"
#include "ui_calculator.h"

#include <QMessagebox>
#include <cmath>
#include <algorithm>
#include <string>
#include <iterator>
#include <QPushButton>
#include <iomanip>
#include <QAction>
#include <queue>
#include <QScopedPointer>
#include <QClipboard>

QPushButton* Button_controler;
QPushButton* comma_counter;
QPushButton* comma_cleaner;
QPushButton* Button_delete;

std::queue<QAction*>Que;

static short flag{};
static short space_flag{};

Calculator::Calculator(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::Calculator)
{

    ui->setupUi(this);

    ui->result_screen->setAlignment(Qt::AlignRight);

    Button_controler = new QPushButton;
    Button_controler->setVisible(0);

    comma_counter = new QPushButton;
    comma_counter->setVisible(0);

    comma_cleaner = new QPushButton;
    comma_cleaner->setVisible(0);

    Button_delete = new QPushButton;
    Button_delete->setVisible(0);

    connect(ui->Button_plus, SIGNAL(clicked()), this, SLOT(on_Button_controler_clicked()));
    connect(ui->Button_divided, SIGNAL(clicked()), this, SLOT(on_Button_controler_clicked()));
    connect(ui->Button_ecual, SIGNAL(clicked()), this, SLOT(on_Button_controler_clicked()));
    connect(ui->Button_minus, SIGNAL(clicked()), this, SLOT(on_Button_controler_clicked()));
    connect(ui->Button_mod, SIGNAL(clicked()), this, SLOT(on_Button_controler_clicked()));
    connect(ui->Button_multiply, SIGNAL(clicked()), this, SLOT(on_Button_controler_clicked()));
    connect(ui->Button_pow, SIGNAL(clicked()), this, SLOT(on_Button_controler_clicked()));
    //////////////////////////////////////////////////////////////////////////////////////
    connect(ui->Button_zero, SIGNAL(clicked()), this, SLOT(on_comma_counter_clicked()));
    connect(ui->Button_one, SIGNAL(clicked()), this, SLOT(on_comma_counter_clicked()));
    connect(ui->Button_tow, SIGNAL(clicked()), this, SLOT(on_comma_counter_clicked()));
    connect(ui->Button_three, SIGNAL(clicked()), this, SLOT(on_comma_counter_clicked()));
    connect(ui->Button_four, SIGNAL(clicked()), this, SLOT(on_comma_counter_clicked()));
    connect(ui->Button_five, SIGNAL(clicked()), this, SLOT(on_comma_counter_clicked()));
    connect(ui->Button_six, SIGNAL(clicked()), this, SLOT(on_comma_counter_clicked()));
    connect(ui->Button_seven, SIGNAL(clicked()), this, SLOT(on_comma_counter_clicked()));
    connect(ui->Button_eight, SIGNAL(clicked()), this, SLOT(on_comma_counter_clicked()));
    connect(ui->Button_nine, SIGNAL(clicked()), this, SLOT(on_comma_counter_clicked()));
    ///////////////////////////////////////////////////////////////////////////////////////
    connect(ui->Button_zero, SIGNAL(clicked()), this, SLOT(on_comma_cleaner_clicked()));
    connect(ui->Button_one, SIGNAL(clicked()), this, SLOT(on_comma_cleaner_clicked()));
    connect(ui->Button_tow, SIGNAL(clicked()), this, SLOT(on_comma_cleaner_clicked()));
    connect(ui->Button_three, SIGNAL(clicked()), this, SLOT(on_comma_cleaner_clicked()));
    connect(ui->Button_four, SIGNAL(clicked()), this, SLOT(on_comma_cleaner_clicked()));
    connect(ui->Button_five, SIGNAL(clicked()), this, SLOT(on_comma_cleaner_clicked()));
    connect(ui->Button_six, SIGNAL(clicked()), this, SLOT(on_comma_cleaner_clicked()));
    connect(ui->Button_seven, SIGNAL(clicked()), this, SLOT(on_comma_cleaner_clicked()));
    connect(ui->Button_eight, SIGNAL(clicked()), this, SLOT(on_comma_cleaner_clicked()));
    connect(ui->Button_nine, SIGNAL(clicked()), this, SLOT(on_comma_cleaner_clicked()));
    connect(ui->Button_ecual,SIGNAL(clicked()),this,SLOT(on_History_clicked()));

    QIcon icon(":/res/img/learning.gif");
    ui->sub_result_screen->addAction(icon, QLineEdit::LeadingPosition);
    ui->result_screen->addAction(ui->clear_icon,QLineEdit::LeadingPosition);
    ui->result_screen->addAction(ui->delete_icon, QLineEdit::ActionPosition::TrailingPosition);
    ui->result_screen->setClearButtonEnabled(1);
    ui->result_screen->setReadOnly(0);
    Button_delete->setVisible(0);
    connect(ui->delete_icon, SIGNAL(triggered()), this, SLOT(on_Button_delete_clicked()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(on_Button_exit_clicked()));

}

Calculator::~Calculator()
{
    delete ui;
    delete Button_controler;
    delete comma_counter;
    delete comma_cleaner;
    delete Button_delete;
}

bool Calculator::is_zero()
{
    if (ui->result_screen->text() == "0")
    {
        return true;
    }
    return false;
}

bool Calculator::is_doted()
{
    for (int i{ 0 }; i < ui->result_screen->text().size(); i++)
    {
        if (ui->result_screen->text().at(i) == '.')return true;
    }
    return false;
}

void Calculator::filter()
{
    auto& temp{ ui->result_screen};

    for (int i{ 0 }; i < temp->text().size(); i++) {

        if ((temp->text().at(i) >= char(48) && temp->text().at(i) <= char(57)))
        {
            continue;
        }
        else
            temp->setText(temp->text().removeAt(i));
    }
}

void Calculator::result(char _operator)
{

    if (is_zero() || ui->result_screen->text() == "")
        return;
    if (flag == 0)
        ui->sub_result_screen->clear();

    short num_length{ 20 };

    if (ui->result_screen->text().contains('.'))num_length = 16;

    for (int x = 0; x < ui->result_screen->text().length(); x++)
    {
        if (ui->result_screen->text().at(x) == ',')
        {
            ui->result_screen->setText(ui->result_screen->text().removeAt(x));
        }
    }

    std::string str = ui->result_screen->text().toStdString();
    t.num = std::stold(str);
    switch (_operator)
    {
    case '+':
    {
        if (flag < 1)
        {
            op.num = t.num;
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()) + "+ ");
            ui->result_screen->clear();
            flag++;
        }
        else
        {
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()));
            ui->result_screen->clear();
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()) + " = ");
            ui->sub_result_screen->setText(ui->sub_result_screen->text() + QString::number(op + t, 'g', num_length));
            ui->result_screen->setText(QString::number(op + t, 'g', num_length));
            on_History_clicked();
            coma_seperator();
            on_comma_cleaner_clicked();
            flag = 0;
        }
        break;
    }
    case '-':
    {
        if (flag < 1) {
            op.num = t.num;
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()) + "- ");
            ui->result_screen->clear();
            flag++;
        }
        else
        {
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()));
            ui->result_screen->clear();
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()) + " = ");
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()) + QString::number(op - t, 'g', num_length));
            ui->result_screen->setText(QString::number(op - t, 'g', num_length));
            on_History_clicked();
            coma_seperator();
            on_comma_cleaner_clicked();
            flag = 0;

        }
        break;
    }
    case '*':
    {
        if (flag < 1) {
            op.num = t.num;
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()) + "* ");
            ui->result_screen->clear();
            flag++;
        }
        else
        {
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()));
            ui->result_screen->clear();
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()) + " = ");
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()) + QString::number(op * t, 'g', num_length));
            on_History_clicked();
            ui->result_screen->setText(QString::number(op * t, 'g', num_length));
            coma_seperator();
            on_comma_cleaner_clicked();
            flag = 0;

        }
        break;
    }
    case '%':
    {
        if (flag < 1)
        {
            op.num = t.num;
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()) + "% ");
            ui->result_screen->clear();
            flag++;
        }
        else
        {
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()));
            ui->result_screen->clear();
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()) + " = ");
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()) + QString::number(op % t, 'g', num_length));
            ui->result_screen->setText(QString::number(op % t, 'g', num_length));
            on_History_clicked();
            coma_seperator();
            on_comma_cleaner_clicked();
            flag = 0;
        }
        break;
    }
    case '^':
    {
        if (flag < 1)
        {
            op.num = t.num;
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()) + "^ ");
            ui->result_screen->clear();
            flag++;
        }
        else
        {
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()));
            ui->result_screen->clear();
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()) + " = ");
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()) + QString::number(op ^ t, 'g', num_length));
            ui->result_screen->setText(QString::number(op ^ t, 'g', num_length));
            on_History_clicked();
            coma_seperator();
            on_comma_cleaner_clicked();
            flag = 0;
        }
        break;
    }
    case '/':
    {
        if (flag < 1)
        {
            op.num = t.num;
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()) + "/ ");
            ui->result_screen->clear();
            flag++;
        }
        else
        {
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()));
            ui->result_screen->clear();
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()) + " = ");
            ui->sub_result_screen->setText(ui->sub_result_screen->text().append(ui->result_screen->text()) + QString::number(op / t, 'g', num_length));
            ui->result_screen->setText(QString::number(op / t, 'g', num_length));
            on_History_clicked();
            coma_seperator();
            on_comma_cleaner_clicked();
            flag = 0;
        }
        break;
    }
    default:
        break;
    }
}
 char Calculator::get_op()
{
    if (ui->sub_result_screen->text().isEmpty())
        return 0;

    int i{};
    for (; i < ui->sub_result_screen->text().length(); i++)
    {
        if (ui->sub_result_screen->text().at(i) == '+')break;
        if (ui->sub_result_screen->text().at(i) == '-')break;
        if (ui->sub_result_screen->text().at(i) == '*')break;
        if (ui->sub_result_screen->text().at(i) == '%')break;
        if (ui->sub_result_screen->text().at(i) == '/')break;
        if (ui->sub_result_screen->text().at(i) == '^')break;
    }

    std::string temp = ui->sub_result_screen->text().toStdString();
    const char t = temp.at(i);
    return t;
}

void Calculator::coma_seperator()
{
    if (ui->result_screen->text().contains('.'))return;

    QString s = ui->result_screen->text();

    for (int i = 0; i < s.length(); i++)
    {
        if (s.at(i) == ',')s.remove(s.at(i));
    }
    ui->result_screen->setText(s);

    short counter{};
    std::vector<QChar>vec;

    for (int index_ = ui->result_screen->text().length() - 1; index_ >= 0; index_--)
    {
        vec.emplace_back(ui->result_screen->text().at(index_));
        counter++;
        if (counter == 3)
        {
            vec.emplace_back(',');
            counter = 0;
        }
    }

    std::reverse(vec.begin(), vec.end());
    QString str;

    for (size_t i = 0; i < vec.size(); i++)str.push_back(vec.at(i));

    ui->result_screen->setText(str);
    if (ui->result_screen->text().at(0) == '-' && ui->result_screen->text().at(1) == ',')ui->result_screen->setText(ui->result_screen->text().removeAt(1));
}

void Calculator::keyPressEvent(QKeyEvent* event)
{
        if (event->key() == Qt::Key_0)
        {
           //TODO
        }
}

void Calculator::resizeEvent(QResizeEvent*)
{
    int WindowWidth = this->size().width();

    if (WindowWidth >= 0 && WindowWidth <= 350)
    {
        QFont font = ui->result_screen->font();
            font.setPointSize(14);
            ui->result_screen->setFont(font);
            return;
    }

    if (WindowWidth >= 351 && WindowWidth <= 500)
    {
        QFont font = ui->result_screen->font();
            font.setPointSize(17);
            ui->result_screen->setFont(font);
            return;
    }

    if (WindowWidth >= 501 && WindowWidth <= 900)
    {
        QFont font = ui->result_screen->font();
            font.setPointSize(25);
            ui->result_screen->setFont(font);
            return;
    }
    if (WindowWidth >= 901 && WindowWidth)
    {
        QFont font = ui->result_screen->font();
        font.setPointSize(52);
        ui->result_screen->setFont(font);
        return;
    }

}

void error_thrown(double &x)
{
    QMessageBox msgbox;
    msgbox.setWindowTitle("Warning!");
    msgbox.setInformativeText("This Result Has Been Thrown\n\n[" + QString::number(x, 'g', 30) + "]\n\nLIMIT REACHED !!!");
    msgbox.setIcon(QMessageBox::Warning);
    QIcon ico(":/res/img/attention.png");
    msgbox.setWindowIcon(ico);
    msgbox.setStandardButtons(QMessageBox::Close);
    QApplication::beep();
    msgbox.exec();
}

void Calculator::on_Button_zero_clicked()
{
    if (is_zero()) return;
    
    ui->result_screen->setText(ui->result_screen->text() + "0");
}

void Calculator::on_Button_one_clicked()
{
    if (is_zero())ui->result_screen->clear();

    ui->result_screen->setText(ui->result_screen->text() + "1");
}

void Calculator::on_Button_tow_clicked()
{
    if (is_zero())ui->result_screen->clear();

    ui->result_screen->setText(ui->result_screen->text() + "2");

}

void Calculator::on_Button_three_clicked()
{
    if (is_zero())ui->result_screen->clear();

    ui->result_screen->setText(ui->result_screen->text() + "3");

}

void Calculator::on_Button_four_clicked()
{
    if (is_zero())ui->result_screen->clear();

    ui->result_screen->setText(ui->result_screen->text() + "4");

}

void Calculator::on_Button_five_clicked()
{
    if (is_zero())ui->result_screen->clear();

    ui->result_screen->setText(ui->result_screen->text() + "5");

}

void Calculator::on_Button_six_clicked()
{
    if (is_zero())ui->result_screen->clear();

    ui->result_screen->setText(ui->result_screen->text() + "6");

}

void Calculator::on_Button_seven_clicked()
{
    if (is_zero())ui->result_screen->clear();

    ui->result_screen->setText(ui->result_screen->text() + "7");
 
}

void Calculator::on_Button_eight_clicked()
{
    if (is_zero())ui->result_screen->clear();

    ui->result_screen->setText(ui->result_screen->text() + "8");

}

void Calculator::on_Button_nine_clicked()
{
    if (is_zero())ui->result_screen->clear();

    ui->result_screen->setText(ui->result_screen->text() + "9");
}

void Calculator::on_Button_dot_clicked()
{
    if (!is_doted())
    {
        if (is_zero())ui->result_screen->clear();

        if (ui->result_screen->text().length() == 0)ui->result_screen->setText(ui->result_screen->text() + "0");

        ui->result_screen->setText(ui->result_screen->text() + ".");
    }
}

void Calculator::on_Button_delete_clicked()
{
    if (ui->result_screen->text().isEmpty())return;

    if (ui->result_screen->text().length() == 2 && ui->result_screen->text().at(0) == '-')
    {
        ui->result_screen->clear();
    }
    else
    {
        ui->result_screen->setText(ui->result_screen->text().removeLast());
    }

    if (ui->result_screen->text() != "")
    {
        coma_seperator();
        on_comma_cleaner_clicked();
    }

    std::string ss = ui->result_screen->text().toStdString();

    if (ss.length() >= 1)
    {
        size_t k = ss.length() - 1;

        if (ss.at(k) == '.')
        {
            ss.erase(k);
        }
        ui->result_screen->setText(ss.c_str());
    }
}

void Calculator::on_Button_plus_clicked()
{
    const char temp = get_op();

    if (!ui->sub_result_screen->text().isEmpty() && temp != '+')on_Button_ecual_clicked();

    result('+');
}

void Calculator::on_Button_minus_clicked()
{
    const char temp = get_op();

    if (!ui->sub_result_screen->text().isEmpty() && temp != '-')on_Button_ecual_clicked();

    result('-');
}

void Calculator::on_Button_divided_clicked()
{
    const char temp = get_op();

    if (!ui->sub_result_screen->text().isEmpty() && temp != '/')on_Button_ecual_clicked();

    result('/');
}

void Calculator::on_Button_pow_clicked()
{
    const char temp = get_op();

    if (!ui->sub_result_screen->text().isEmpty() && temp != '^')on_Button_ecual_clicked();

    result('^');
}

void Calculator::on_Button_mod_clicked()
{
    const char temp = get_op();

    if (!ui->sub_result_screen->text().isEmpty() && temp != '%')on_Button_ecual_clicked();

    result('%');
}

void Calculator::on_Button_multiply_clicked()
{
    const char temp = get_op();

    if (!ui->sub_result_screen->text().isEmpty() && temp != '*')on_Button_ecual_clicked();

    result('*');
}

void Calculator::on_Button_clear_clicked()
{
    ui->sub_result_screen->clear();
    ui->result_screen->clear();
    t.num = 0;
    op.num = 0;
    flag = 0;
   space_flag = 0;
}

void Calculator::on_comma_counter_clicked()
{
    if (ui->result_screen->text() == "" || ui->result_screen->text() == "0")return;

    coma_seperator();
}

void Calculator::on_comma_cleaner_clicked()
{
    if (ui->result_screen->text().at(0) == ',') 
        ui->result_screen->setText(ui->result_screen->text().removeAt(0));
}

void Calculator::on_result_screen_textEdited()
{
    filter();

    if (ui->result_screen->text().length() >= 3)
    {
        coma_seperator();
        on_comma_cleaner_clicked();
    }
}

void Calculator::on_Button_minus_plus_clicked()
{
    if (ui->result_screen->text().isEmpty() || ui->result_screen->text() == '0')return;

     short minus_flag{};

    for (int y = 0; y < ui->result_screen->text().length() - 1; y++)
    {
        if (ui->result_screen->text().at(y) == char(45))
        {
            ui->result_screen->setText(ui->result_screen->text().removeAt(y));
            minus_flag++;
            break;
        }
    }
    if (minus_flag == 0)
    {
        QString ss = ui->result_screen->text();
        ui->result_screen->setText('-' + ss);
    }
}

void Calculator::on_Button_exit_clicked()
{
    QApplication::exit();
}

void Calculator::on_actionOn_Top_triggered()
{
    if (ui->actionOn_Top->isChecked())
    {
        this->setWindowFlags(Qt::WindowStaysOnTopHint);
        this->show();
    }
    else
    {
        this->setWindowFlags(Qt::Window);
        this->show();
    }
}

void Calculator::on_Button_controler_clicked()
{

    if (ui->sub_result_screen->text().isEmpty())return;

    if (ui->sub_result_screen->text().contains('='))return;

    short minus_flag{};
    if(ui->sub_result_screen->text().at(0) == '-')
    {
        ui->sub_result_screen->setText(ui->sub_result_screen->text().removeFirst());
        minus_flag++;
    }

     int i{};
     for (; i < ui->sub_result_screen->text().length(); i++)
     {
         if (ui->sub_result_screen->text().at(i) == '+')break;
         if (ui->sub_result_screen->text().at(i) == '-')break;
         if (ui->sub_result_screen->text().at(i) == '*')break;
         if (ui->sub_result_screen->text().at(i) == '%')break;
         if (ui->sub_result_screen->text().at(i) == '/')break;
         if (ui->sub_result_screen->text().at(i) == '^')break;
     }

    short spacer = i - 1;

    if (space_flag == 0)
    {
        if (ui->sub_result_screen->text().at(spacer) != ' ')
            if (ui->sub_result_screen->text().at(i) == '-' ||
                ui->sub_result_screen->text().at(i) == '+' ||
                ui->sub_result_screen->text().at(i) == '*' ||
                ui->sub_result_screen->text().at(i) == '/' ||
                ui->sub_result_screen->text().at(i) == '^' ||
                ui->sub_result_screen->text().at(i) == '%')
            {
                ui->sub_result_screen->setText(ui->sub_result_screen->text().insert(i, ' '));
                space_flag++;
            }
    }

    QChar cr = ui->sub_result_screen->text().at(i);

    QObject* Button = QObject::sender();

    if (cr == '+' || cr == '*' ||
        cr == '^' || cr == '-' ||
        cr == '%' || cr == '/')
    {
        if (Button == ui->Button_plus)
        {
            ui->sub_result_screen->setText(ui->sub_result_screen->text().removeAt(i));
            ui->sub_result_screen->setText(ui->sub_result_screen->text().insert(i, '+'));
            space_flag = 0;
        }

        else if (Button == ui->Button_minus)
        {
            ui->sub_result_screen->setText(ui->sub_result_screen->text().removeAt(i));
            ui->sub_result_screen->setText(ui->sub_result_screen->text().insert(i, '-'));
            space_flag = 0;
        }
        else if (Button == ui->Button_multiply)
        {
            ui->sub_result_screen->setText(ui->sub_result_screen->text().removeAt(i));
            ui->sub_result_screen->setText(ui->sub_result_screen->text().insert(i, '*'));
            space_flag = 0;
        }
        else if (Button == ui->Button_mod)
        {
            ui->sub_result_screen->setText(ui->sub_result_screen->text().removeAt(i));
            ui->sub_result_screen->setText(ui->sub_result_screen->text().insert(i, '%'));
            space_flag = 0;
        }
        else if (Button == ui->Button_pow)
        {
            ui->sub_result_screen->setText(ui->sub_result_screen->text().removeAt(i));
            ui->sub_result_screen->setText(ui->sub_result_screen->text().insert(i, '^'));
            space_flag = 0;
        }
        else if (Button == ui->Button_divided)
        {
            ui->sub_result_screen->setText(ui->sub_result_screen->text().removeAt(i));
            ui->sub_result_screen->setText(ui->sub_result_screen->text().insert(i, '/'));
            space_flag = 0;
        }

    }
    if (minus_flag > 0)
    {
        ui->sub_result_screen->setText(ui->sub_result_screen->text().insert(0,'n'));

    }
}

void Calculator::on_Button_ecual_clicked()
{
    if (ui->sub_result_screen->text().isEmpty())return;
    if (ui->sub_result_screen->text().contains('='))return;

    space_flag = 0;
    int i{};
    for (; i < ui->sub_result_screen->text().length(); i++)
    {
        if (ui->sub_result_screen->text().at(i) == '+')break;
        if (ui->sub_result_screen->text().at(i) == '-')break;
        if (ui->sub_result_screen->text().at(i) == '*')break;
        if (ui->sub_result_screen->text().at(i) == '%')break;
        if (ui->sub_result_screen->text().at(i) == '/')break;
        if (ui->sub_result_screen->text().at(i) == '^')break;
    }

    std::string temp = ui->sub_result_screen->text().toStdString();
    const char it = temp.at(i);

    switch (it)
    {
    case '+':
    {
        on_Button_plus_clicked();
        break;
    }
    case '-':
    {
        on_Button_minus_clicked();
        break;
    }
    case '*':
    {
        on_Button_multiply_clicked();
        break;
    }
    case '/':
    {
        on_Button_divided_clicked();
        break;
    }
    case '%':
    {
        on_Button_mod_clicked();
        break;
    }
    case '^':
    {
        on_Button_pow_clicked();
        break;
    }
    default:
        break;
    }

}

void Calculator::on_History_clicked()
{
    static short size_flag{};
    static short sep_flag{};
    static QString previous_str{"NULL"};
    static std::queue<QAction*>Sep_Que;

    if(size_flag > 10)
    {
        ui->menuHistory->removeAction(Que.front());

        Que.pop();

        size_flag--;
    }
    if(sep_flag > 9)
    {
        ui->menuHistory->removeAction(Sep_Que.front());
        Sep_Que.pop();
        sep_flag--;
    }

    if(ui->sub_result_screen->text().contains("="))
    {
        if(ui->sub_result_screen->text() != previous_str)
        {
            QAction* action = new QAction;
            QAction* sep = new QAction;
            sep->setSeparator(1);

        action->setText(ui->sub_result_screen->text());
        action->setIcon(QIcon(":/res/img/restore.png"));
        action->setIconVisibleInMenu(1);

    ui->menuHistory->insertAction(ui->actionHistory_List,action);
        ui->menuHistory->insertAction(action,sep);

        previous_str = action->text();
        Sep_Que.emplace(sep);
        Que.emplace(action);
        connect(action,SIGNAL(triggered()),this,SLOT(on_History_Item_clicked()));
        size_flag++;
        sep_flag++;
        }
    }
}

void Calculator::on_History_Item_clicked()
{
    QClipboard *clipboard = QGuiApplication::clipboard();

    QObject* action_sender = QObject::sender();

    std::queue<QAction*>Q = Que;

    while(!Q.empty())
    {
        if(action_sender == Q.front())
        {
    std::string final;
    std::string str = Q.front()->text().toStdString();
    for(size_t x = 0,end = str.length();x < str.length();x++)
    {
                if(str.at(x) == '=')
                {
                    final = str.substr(x+2,end);
                    break;
                }
    }
     clipboard->setText(final.c_str());
    break;
        }
        else
        {
     Q.pop();
        }
    }
}

