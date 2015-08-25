package org.eclipse.bI;

import org.eclipse.jface.action.IAction;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.IWorkbenchWindowActionDelegate;

public class Action implements IWorkbenchWindowActionDelegate {

	@Override
	public void run(IAction arg0) {
		// TODO Auto-generated method stub
		Shell shell = activeWindow.getShell();
		MessageDialog.openInformation(shell, "Hello World", "Hello World!");		
	}

	@Override
	public void selectionChanged(IAction arg0, ISelection arg1) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void dispose() {
		// TODO Auto-generated method stub
		
	}
	
	IWorkbenchWindow activeWindow = null;

	@Override
	public void init(IWorkbenchWindow arg0) {
		activeWindow=arg0;
	}

}
