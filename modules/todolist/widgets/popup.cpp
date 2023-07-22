#include "popup.h"

#include "filters.h"
#include "../tools/logger.h"

PopUp::PopUp(QStringList prompts, QString title, QWidget *p)
    : Clickable([this](QMouseEvent *e) {
        QRect r = content->rect();
        r.translate(content->pos());
        if (!r.contains(e->pos())) {
            emit result(true, QStringList());
            deleteLater();
        }
    }, p)
{
    lay = new QHBoxLayout(this);
    content = new QWidget(this);
    contentLay = new QVBoxLayout(content);
    header = new QLabel(title, content);
    buttonContainer = new QWidget(content);
    buttonLay = new QHBoxLayout(buttonContainer);
    okButton = new QPushButton("Ok", buttonContainer);
    cancelButton = new QPushButton("Cancel", buttonContainer);

    buttonLay->addStretch();
    buttonLay->addWidget(okButton);
    buttonLay->addSpacing(5);
    buttonLay->addWidget(cancelButton);
    buttonLay->addStretch();

    contentLay->addWidget(header);
    for (qsizetype i = 0 ; i < prompts.size() ; i++) {
        QLineEdit *input = new QLineEdit(content);
        input->setPlaceholderText(prompts[i]);
        contentLay->addWidget(input);
        inputs.push_back(input);
        input->setProperty("class", "popup-input");
        if (i == prompts.size() - 1) {
            QObject::connect(input, &QLineEdit::returnPressed, [this]() {
                QStringList prompts;
                for (auto input : inputs) {
                    prompts.append(input->text());
                }
                emit result(false, prompts);
            });
        } else {
            QObject::connect(input, &QLineEdit::returnPressed, [this, i]() {
                inputs[i+1]->setFocus();
            });
        }
    }
    contentLay->addWidget(buttonContainer);

    lay->addStretch();
    lay->addWidget(content, 0, Qt::AlignVCenter);
    lay->addStretch();

    content->setProperty("class", "popup-content");
    header->setProperty("class", "popup-header");
    okButton->setProperty("class", "popup-ok");
    cancelButton->setProperty("class", "popup-cancel");
    setProperty("class", "popup");

    setAttribute(Qt::WA_StyledBackground);
    setFixedSize(p->size());
    show();

    QObject::connect(okButton, &QPushButton::clicked, [this]() {
        QStringList prompts;
        for (auto input : inputs) {
            prompts.append(input->text());
        }
        emit result(false, prompts);
    });
    QObject::connect(cancelButton, &QPushButton::clicked, [this]() {
        emit result(true, QStringList());
    });
}