#include "mainwindow.h"

#include <QApplication>

class MyWidget : public QMainWindow, private Ui::FileWorker
{
public:
    MyWidget(QWidget *parent = nullptr)
        : QMainWindow(parent)
    {
        setupUi(this);

        connect(menu_lineEdit, &QLineEdit::returnPressed, menu_pushButton, &QPushButton::click);
        connect(menu_pushButton, &QPushButton::clicked, this, &MyWidget::callFunction);
    }

private slots:
    void callFunction()
    {
        int number = menu_lineEdit->text().toInt();
        menu_lineEdit->clear();
        switch (number)
        {
        case 1:
            FileLoad();
            break;

        case 2:
            FilePrint();
            break;

        case 3:
            FileUpdate();
            break;

        case 4:
            FileDelele();
            break;

        case 5:
            FileFind();
            break;

        case 6:
            FileSave();
            break;

        case 7:
            Exit();
            break;

        default:
            QMessageBox::warning(this, "Error", "유효하지 않은 명령번호입니다!");
            break;
        }
    }

    QString m_fileName;
    QString m_fileContent;

    void FileLoad()
    {
        QString fileName = QFileDialog::getOpenFileName(this, "FileLoad", QDir::homePath());

        QFileInfo fileInfo(fileName);
        QString extension = fileInfo.suffix();
        if (extension != "txt") {
            QMessageBox::warning(this, "FileLoad", ".txt 확장자 파일이 아닙니다!");
            return;
        }

        if (!fileName.isEmpty())
        {
            QFile file(fileName);

            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                m_fileName = fileName;
                m_fileContent = file.readAll();
                file.close();
                QMessageBox::information(this, "FileLoad", "파일 불러오기 성공!");
            }
            else
            {
                QMessageBox::warning(this, "FileLoad", "파일 불러오기 실패!");
            }
        }
    }

    void FilePrint()
    {
        txt_textBrowser->setPlainText(m_fileContent);
    }

    void FileUpdate()
    {
        QString oldWord = QInputDialog::getText(this, tr("FileUpdate"), tr("바꿀 문자열을 입력하세요 :"));
        QString newWord = QInputDialog::getText(this, tr("FileUpdate"), tr("새 문자열을 입력하세요 :"));

        if (!oldWord.isEmpty() && !newWord.isEmpty())
        {
            m_fileContent.replace(oldWord, newWord);
            txt_textBrowser->setText(m_fileContent);
        }
    }

    void FileDelele()
    {
        QString word = QInputDialog::getText(this, tr("FileDelele"), tr("삭제할 문자열을 입력하세요 :"));

        if (!word.isEmpty())
        {
            m_fileContent.replace(word, "");
            txt_textBrowser->setText(m_fileContent);
        }
    }

    void FileFind()
    {
        FilePrint();

        QString word = QInputDialog::getText(this, tr("FileFind"), tr("검색할 문자열을 입력하세요 :"));

        if (!word.isEmpty())
        {
            QTextDocument *document = txt_textBrowser->document();
            QTextCursor cursor(document);
            QTextCharFormat format;
            format.setBackground(Qt::yellow);

            bool found = false;
            while (!cursor.isNull()) {
                cursor.clearSelection();
                cursor = document->find(word, cursor);

                if (!cursor.isNull()) {
                    found = true;
                    QTextCursor highlightCursor(document);
                    highlightCursor.setPosition(cursor.selectionStart());
                    highlightCursor.setPosition(cursor.selectionEnd(), QTextCursor::KeepAnchor);
                    highlightCursor.mergeCharFormat(format);
                    cursor.movePosition(QTextCursor::NextCharacter);
                }
            }

            if (!found) {
                QMessageBox::information(this, tr("FileFind"), tr("입력하신 문자열은 해당 파일에 존재하지 않습니다!"));
            }
        }
    }

    void FileSave()
    {
        QString filePath = QFileDialog::getSaveFileName(this, tr("FileSave"), "", tr("Text Files (*.txt)"));

        if (!filePath.isEmpty())
        {
            QFile file(filePath);

            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream out(&file);
                out << txt_textBrowser->toPlainText();
                file.close();

                QMessageBox::information(this, "FileSave", "파일이 성공적으로 저장되었습니다!");
            }
            else
            {
                QMessageBox::warning(this, "FileSave", "파일 저장에 실패하였습니다!");
            }
        }
    }

    void Exit()
    {
        QApplication::quit();
    }

};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MyWidget widget;
    widget.show();

    return app.exec();
}
