#!/usr/bin/python
# -*- coding: utf-8 -*-

"""
read excel and write to word
"""

import win32com.client
import os


def open_word(src_word):
    """open word src_word,return handle if success,return None if failed"""

    try:
        word1 = win32com.client.Dispatch('Word.application')
    except:
        print '''
\xb4\xb4\xbd\xa8Word\xb6\xd4\xcf\xf3\xca\xa7\xb0\xdc
'''
        return None
    if os.path.exists(src_word):
        try:
            doc = word1.Documents.Open(src_word)
        except:
            print '''
\xb4\xf2\xbf\xaa%s\xca\xa7\xb0\xdc\xa3\xac\xc7\xeb\xbc\xec\xb2\xe9\xce\xc4\xbc\xfe\xc3\xfb
''' \
                % src_word
            word1.Quit()
            return None
    else:
        print '''
\xb4\xf2\xbf\xaa\xce\xc4\xbc\xfe\xca\xa7\xb0\xdc: %s\xb2\xbb\xb4\xe6\xd4\xda
''' \
            % src_word
        word1.Quit()
        return None
    return doc


def open_excel(src_excel):
    """open excel file src_excel,return file handle if success,return None if failed"""

    try:
        excel1 = win32com.client.Dispatch('Excel.application')
    except:
        print '\n\xb4\xb4\xbd\xa8Excel\xb6\xd4\xcf\xf3\xca\xa7\xb0\xdc'
        return None
    if os.path.exists(src_excel):
        try:
            book = excel1.Workbooks.open(src_excel)
        except:
            print '''
\xb4\xf2\xbf\xaa%s\xca\xa7\xb0\xdc\xa3\xac\xc7\xeb\xbc\xec\xb2\xe9\xce\xc4\xbc\xfe\xc3\xfb
''' \
                % src_excel
            excel1.Quit()
            return None
    else:
        print '''
\xb4\xf2\xbf\xaa\xce\xc4\xbc\xfe\xca\xa7\xb0\xdc: %s\xb2\xbb\xb4\xe6\xd4\xda
''' \
            % src_excel
        excel1.Quit()
        return None
    return book


def write_word():
    print '\xca\xe4\xc8\xebword\xce\xc4\xbc\xfe\xb5\xc4\xc2\xb7\xbe\xb6\xa3\xac\xbf\xc9\xd2\xd4\xb0\xfc\xba\xac\xd6\xd0\xce\xc4\xa3\xac\xc0\xfd\xc8\xe7 d:\\\xb6\xa9\xc6\xb11\\\xb6\xa9\xc6\xb11.doc'
    src_word = raw_input('word\xce\xc4\xbc\xfe\xc3\xfb: ')
    doc1 = open_word(src_word)
    if doc1 == None:
        return None

    print '\n\xca\xe4\xc8\xebexcel\xce\xc4\xbc\xfe\xb5\xc4\xc2\xb7\xbe\xb6\xa3\xac\xbf\xc9\xd2\xd4\xb0\xfc\xba\xac\xd6\xd0\xce\xc4\xa3\xac\xc0\xfd\xc8\xe7 d:\\\xb6\xa9\xc6\xb12\\\xb6\xa9\xc6\xb12.xls'
    src_excel = raw_input('Excel\xce\xc4\xbc\xfe\xc3\xfb: ')
    excel1 = open_excel(src_excel)
    if excel1 == None:
        doc1.Close()
        return None

    print '\n\xd5\xfd\xd4\xda\xb4\xa6\xc0\xed\xa3\xac\xc7\xeb\xc9\xd4\xba\xf2...'

    # excel1.Visible=1
    # word1.Visible=1

    row = 1
    while 1:
        row = row + 1
        if excel1.Sheets(1).Cells(row, 9).value == None:
            print '\n\xb6\xc1\xc8\xebexcel\xbd\xe1\xca\xf8,\xb9\xb2\xb6\xc1\xc8\xeb%d\xd0\xd0' \
                % (row - 1)
            break
        if len(excel1.Sheets(1).Cells(row, 9).value) != 18 \
            and len(excel1.Sheets(1).Cells(row, 9).value) != 15:
            print '''
\xc9\xed\xb7\xdd\xd6\xa4\xba\xc5\xc2\xeb\xd3\xd0\xce\xf3,\xb5\xda%d\xd0\xd0\xb5\xda9\xc1\xd0\xa3\xac%s %s
''' \
                % (row, excel1.Sheets(1).Cells(row, 8),
                   excel1.Sheets(1).Cells(row, 9))
            doc1.Save()
            doc1.Close()
            excel1.Close()
            exit(1)

        word_rows = doc1.Tables(1).Rows.count
        if word_rows < row:
            try:
                doc1.Tables(1).Rows.Add()
            except:
                print '\xd4\xf6\xbc\xd3\xd0\xd0\xb3\xf6\xb4\xed\xa3\xac\xd4\xdaword \xb1\xed\xb8\xf11\xb5\xda%d\xd0\xd0' \
                    % word_rows

                # word1.ActiveDocument.Save()
                # word1.Quit()

                excel1.Close()
                doc1.Save()
                doc1.Close()
                exit(1)
            word_rows = doc1.Tables(1).Rows.count

        for cell in range(1, 10):
            try:
                doc1.Tables(1).Rows(row).Cells(cell).Range.Text = \
                    excel1.Sheets(1).Cells(row, cell)
            except:
                print '\n\xd0\xb4\xc8\xebword %s\xb3\xf6\xb4\xed,\xd4\xdaexcel %s\xb5\xda%d \xd0\xd0' \
                    % (src_word, src_excel, row)

                # word1.ActiveDocument.Save()

                doc1.Save()
                doc1.Close()
                excel1.Close()
                exit(1)

    # save
    # word1.ActiveDocument.Save()

    doc1.Save()
    doc1.Close()
    excel1.Close()
    print '''
\xd0\xb4\xc8\xebword\xb3\xc9\xb9\xa6,\xc7\xeb\xb4\xf2\xbf\xaa %s \xb2\xe9\xbf\xb4
''' \
        % src_word


if __name__ == '__main__':
    print '\n'
    write_word()
