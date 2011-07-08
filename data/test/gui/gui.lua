
--button test
function dlg_btn_ok_onclick(self, event)
    guiex.GetSystem():GetUICanvas():CloseDialog( self:GetParent());
end

function OnBtnClick_test1(self, event)
	local dlg = guiex.GetSystem():GetWidgetManager():LoadDynamicPage( "dialog_ok.xml", "common", self:GetSceneName() );
	dlg:GetChild("dlg_ok_button_ok"):RegisterScriptCallbackFunc("OnMouseLeftClick", "dlg_btn_ok_onclick");
	dlg:GetChild("dlg_ok_content"):SetTextContentUTF8("hello dialog!");
	guiex.GetSystem():GetUICanvas():OpenDialog(dlg);
end


--progress test
function OnLoad_Progress1( self, event )
	self:RegisterTimer( "Timer_Update", 0.033 );
end

function OnTimer_Progress1( self, event )
	local curValue = self:GetCurrentValue();
	local maxValue = self:GetMaxValue();
	curValue = curValue + 1;
	if( curValue > maxValue ) then
		curValue = 0;
	end
	self:SetCurrentValue( curValue );
end
