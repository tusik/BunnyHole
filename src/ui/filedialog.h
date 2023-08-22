﻿#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QObject>
#include <QFileDialog>
#include <QListView>
#include <QTreeView>
#include <QPushButton>
#include <QEvent>
class FileDialog : public QFileDialog{
    Q_OBJECT
private:
    QListView *m_listView;
    QTreeView *m_treeView;
    QPushButton *m_btnOpen;
    QStringList m_selectedFiles;

public slots:
    void chooseClicked();
public:
    FileDialog();
    QStringList selectedFiles();
    bool eventFilter(QObject* watched, QEvent* event);
};

#endif // FILEDIALOG_H
