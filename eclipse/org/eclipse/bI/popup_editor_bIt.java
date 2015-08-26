package org.eclipse.bI;

import org.eclipse.jface.action.IAction;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.ui.IEditorActionDelegate;
import org.eclipse.ui.IEditorPart;

public class popup_editor_bIt implements IEditorActionDelegate {
	
	IAction action;
	IEditorPart editor;

	@Override
	public void run(IAction arg0) {
		// TODO Auto-generated method stub
		editor.doSaveAs();
	}

	@Override
	public void selectionChanged(IAction arg0, ISelection arg1) {
		// TODO Auto-generated method stub
	}

	@Override
	public void setActiveEditor(IAction arg0, IEditorPart arg1) {
		action=arg0;
		editor=arg1;
	}

}
