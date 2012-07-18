# -*- coding: utf-8 -*-
#
# Copyright (c) 2008-2012 the MansOS team. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#  * Redistributions of source code must retain the above copyright notice,
#    this list of  conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
# OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
# OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

import wx

class OutputArea(wx.Panel):
    def __init__(self, parent, API, nr):
        wx.Panel.__init__(self, parent)
        sizer = wx.BoxSizer(wx.HORIZONTAL)
        self.API = API
        self.nr = nr
        self.outputArea = wx.TextCtrl(self, style = wx.TE_MULTILINE)
        self.outputArea.SetBackgroundColour("black")
        self.outputArea.SetForegroundColour("white")
        self.outputArea.SetEditable(False)
        sizer.Add(self.outputArea, 2, wx.EXPAND | wx.ALL, 5)
        self.SetBackgroundColour("white")
        self.SetSizerAndFit(sizer)
        self.SetAutoLayout(1)

    def printLine(self, text, clear = False, forceSwitching = True):
        # TODO moves cursor to output area, away from editor if cursor was there!
        #self.API.outputTools.SetSelection(self.nr)
        if clear:
            self.clear()
        if not text:
            text = "\n"
        self.outputArea.AppendText(text)
        self.outputArea.ScrollLines(1)
        if forceSwitching:
            if self == self.API.infoArea:
                self.API.frame.auiManager.ShowPane(self, True)
            elif self == self.API.outputArea:
                self.API.frame.auiManager.ShowPane(self.API.listenModule, True)
            else:
                assert False, "Output window identity crysis!"

    def clear(self):
        self.outputArea.Clear()
