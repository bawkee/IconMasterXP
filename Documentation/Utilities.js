function pop(id)
{
	hhctrl.TextPopup(id, popfont, 6, 6, -1, -1);
}

function show(id)
{
	var idAnchor = 'a_' + id;
	var idDiv = 'd_' + id;
	
	var divElem = document.getElementById(idDiv);
	var anchorElem = document.getElementById(idAnchor);
	
	if (divElem.style.display == 'none' || divElem.style.display == '')
	{
		divElem.style.display = 'block';
		anchorElem.style.backgroundImage = 'url(\'minus.gif\')';
	}
	else
	{
		divElem.style.display = 'none';
		anchorElem.style.backgroundImage = 'url(\'plus.gif\')';
	}
}