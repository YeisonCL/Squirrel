#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    instructionFormat.setForeground(Qt::cyan);
    instructionFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;

    keywordPatterns
    << "\\bMOVS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bANDS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bEORS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bSUBS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bRSBS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bADDS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bADCS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bSBCS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bRSCS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bTSTS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bTEQS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bORRS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bBICS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bMVNS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bCMPS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bCMNS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bLSLS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bLSRS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bASRS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bRRXS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bRORS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bMULS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bMLAS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bUMULLS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bUMLALS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bSMULLS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bSMLALS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bSTRS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bLDRS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bSTRBS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bLDRBS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bSTRHS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bLDRHS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bLDRSBS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bLDRSHS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bBS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b"
    << "\\bBLS?(EQ|NE|CS|HS|CC|LO|MI|PL|VS|VC|HI|LS|GE|LT|GT|LE|AL)?\\b";


    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.pattern.setCaseSensitivity(Qt::CaseInsensitive);
        rule.format = instructionFormat;
        highlightingRules.append(rule);
    }

    registersFormat.setForeground(Qt::magenta);
    keywordPatterns.clear();
    keywordPatterns << "\\bR0\\b" << "\\bR1\\b"
                    << "\\bR2\\b" << "\\bR3\\b" << "\\bR4\\b"
                    << "\\bR5\\b" << "\\bR6\\b" << "\\bR7\\b"
                    << "\\bR8\\b" << "\\bR9\\b" << "\\bR10\\b"
                    << "\\bR11\\b" << "\\bR12\\b" << "\\bR13\\b"
                    << "\\bR14\\b" << "\\bR15\\b" << "\\bPC\\b"
                    << "\\bSP\\b" << "\\bLR\\b";
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegExp(pattern);
        rule.pattern.setCaseSensitivity(Qt::CaseInsensitive);
        rule.format = registersFormat;
        highlightingRules.append(rule);
    }

    labelsFormat.setForeground(Qt::white);
    rule.pattern = QRegExp("[a-zA-Z][a-zA-Z0-9_]*");
    rule.format = labelsFormat;
    highlightingRules.append(rule);

    immediateFormat.setForeground(Qt::white);
    rule.pattern = QRegExp("#[+|-]?(0[x|X])?[a-fA-F0-9]+");
    rule.format = immediateFormat;
    highlightingRules.append(rule);

    commentFormat.setForeground(Qt::gray);
    rule.pattern = QRegExp(";.*");
    rule.format = commentFormat;
    highlightingRules.append(rule);

    normalSymFormat.setForeground(Qt::lightGray);
    rule.pattern = QRegExp("[\\[\\],]");
    rule.format = normalSymFormat;
    highlightingRules.append(rule);

    specialSymFormat.setForeground(Qt::red);
    specialSymFormat.setFontWeight(QFont::Bold);
    rule.pattern = QRegExp("[!#]");
    rule.format = specialSymFormat;
    highlightingRules.append(rule);
}

void Highlighter::highlightBlock(const QString &text){
    QVector<int> matchedIndex;
    foreach (const HighlightingRule &rule, highlightingRules) {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
            if (!matchedIndex.contains(index)){
                setFormat(index, length, rule.format);
                matchedIndex.append(index);
            }

            index = expression.indexIn(text, index + length);
        }
    }
}
