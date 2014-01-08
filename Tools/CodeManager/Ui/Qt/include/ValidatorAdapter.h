#ifndef PSLRK_TOOLS_CODE_MANAGER_UI_QT_VALIDATOR_H
#define PSLRK_TOOLS_CODE_MANAGER_UI_QT_VALIDATOR_H

#include <QValidator>
#include <Validator.h>



class ValidatorHexViewAdapter : public QValidator
{
    Q_OBJECT

    public:
        virtual State validate (QString & input, int & pos) const override
        {
            if (Pslrk::Core::viewIsValid != Pslrk::Core::Validator::ValidateHexView (input.toStdString () ) ) {
                return QValidator::Invalid;
            }
            else {
                return QValidator::Acceptable;
            }
        };

        virtual void  fixup (QString & input) const override
        {
        };
};



class ValidatorStringViewAdapter : public QValidator
{
    Q_OBJECT

    public:
        virtual State validate (QString & input, int & pos) const override
        {
            if (Pslrk::Core::viewIsValid != Pslrk::Core::Validator::ValidateStringView (input.toStdString () ) ) {
                return QValidator::Invalid;
            }
            else {
                return QValidator::Acceptable;
            }
        };

        virtual void  fixup (QString & input) const override
        {
        };
};

#endif//PSLRK_TOOLS_CODE_MANAGER_UI_QT_VALIDATOR_H
