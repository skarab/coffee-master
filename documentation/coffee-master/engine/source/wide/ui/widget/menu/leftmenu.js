function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6452\" class=\"headerLeftMenuInActive\"><a id=\"aID6452\" href=\"#\" OnMouseOver=\"link('_dir','menu0',this)\" class=\"leftMenuLinkHeadInActive\">menu</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1026\" class=\"leftMenuInActive\"><a id=\"aID1026\" href=\"#\" OnMouseOver=\"link('_class','Menu45101',this)\" class=\"leftMenuLinkInActive\">Menu</a></div>\n");
document.write("<div id=\"divID1027\" class=\"leftMenuInActive\"><a id=\"aID1027\" href=\"#\" OnMouseOver=\"link('_class','MenuItem45101',this)\" class=\"leftMenuLinkInActive\">MenuItem</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6245\" class=\"leftMenuInActive\"><a id=\"aID6245\" href=\"#\" OnMouseOver=\"link('_member','MENU_ITEM_TYPE1141535755',this)\" class=\"leftMenuLinkInActive\">MENU_ITEM_TYPE</a></div>\n");
document.write("<div id=\"divID6246\" class=\"leftMenuInActive\"><a id=\"aID6246\" href=\"#\" OnMouseOver=\"link('_member','MENU_STYLE1141535755',this)\" class=\"leftMenuLinkInActive\">MENU_STYLE</a></div>\n");
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
