function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6422\" class=\"headerLeftMenuInActive\"><a id=\"aID6422\" href=\"#\" OnMouseOver=\"link('_dir','selection0',this)\" class=\"leftMenuLinkHeadInActive\">selection</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID947\" class=\"leftMenuInActive\"><a id=\"aID947\" href=\"#\" OnMouseOver=\"link('_class','SelectionManager39455',this)\" class=\"leftMenuLinkInActive\">SelectionManager</a></div>\n");
document.write("<div id=\"divID948\" class=\"leftMenuInActive\"><a id=\"aID948\" href=\"#\" OnMouseOver=\"link('_class','SelectionUndo39455',this)\" class=\"leftMenuLinkInActive\">SelectionUndo</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
