function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6497\" class=\"headerLeftMenuInActive\"><a id=\"aID6497\" href=\"#\" OnMouseOver=\"link('_dir','selection_controller0',this)\" class=\"leftMenuLinkHeadInActive\">selection_controller</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1113\" class=\"leftMenuInActive\"><a id=\"aID1113\" href=\"#\" OnMouseOver=\"link('_class','SelectionController22483',this)\" class=\"leftMenuLinkInActive\">SelectionController</a></div>\n");
document.write("<div id=\"divID6185\" class=\"leftMenuInActive\"><a id=\"aID6185\" href=\"#\" OnMouseOver=\"link('_class','Window0',this)\" class=\"leftMenuLinkInActive\">Window</a></div>\n");
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
