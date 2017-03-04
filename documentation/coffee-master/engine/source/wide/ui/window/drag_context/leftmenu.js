function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6464\" class=\"headerLeftMenuInActive\"><a id=\"aID6464\" href=\"#\" OnMouseOver=\"link('_dir','drag_context0',this)\" class=\"leftMenuLinkHeadInActive\">drag_context</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1041\" class=\"leftMenuInActive\"><a id=\"aID1041\" href=\"#\" OnMouseOver=\"link('_class','DragContext49249',this)\" class=\"leftMenuLinkInActive\">DragContext</a></div>\n");
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
