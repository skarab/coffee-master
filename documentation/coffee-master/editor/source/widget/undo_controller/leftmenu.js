function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6498\" class=\"headerLeftMenuInActive\"><a id=\"aID6498\" href=\"#\" OnMouseOver=\"link('_dir','undo_controller0',this)\" class=\"leftMenuLinkHeadInActive\">undo_controller</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1114\" class=\"leftMenuInActive\"><a id=\"aID1114\" href=\"#\" OnMouseOver=\"link('_class','UndoController22483',this)\" class=\"leftMenuLinkInActive\">UndoController</a></div>\n");
document.write("<div id=\"divID1115\" class=\"leftMenuInActive\"><a id=\"aID1115\" href=\"#\" OnMouseOver=\"link('_class','UndoList22483',this)\" class=\"leftMenuLinkInActive\">UndoList</a></div>\n");
document.write("<div id=\"divID6195\" class=\"leftMenuInActive\"><a id=\"aID6195\" href=\"#\" OnMouseOver=\"link('_class','Window0',this)\" class=\"leftMenuLinkInActive\">Window</a></div>\n");
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
