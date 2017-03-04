function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6423\" class=\"headerLeftMenuInActive\"><a id=\"aID6423\" href=\"#\" OnMouseOver=\"link('_dir','undo0',this)\" class=\"leftMenuLinkHeadInActive\">undo</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID949\" class=\"leftMenuInActive\"><a id=\"aID949\" href=\"#\" OnMouseOver=\"link('_class','UndoGroup39455',this)\" class=\"leftMenuLinkInActive\">UndoGroup</a></div>\n");
document.write("<div id=\"divID950\" class=\"leftMenuInActive\"><a id=\"aID950\" href=\"#\" OnMouseOver=\"link('_class','UndoManager39455',this)\" class=\"leftMenuLinkInActive\">UndoManager</a></div>\n");
document.write("<div id=\"divID951\" class=\"leftMenuInActive\"><a id=\"aID951\" href=\"#\" OnMouseOver=\"link('_class','UndoObject39455',this)\" class=\"leftMenuLinkInActive\">UndoObject</a></div>\n");
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
