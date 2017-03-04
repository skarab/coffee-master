function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6269\" class=\"headerLeftMenuInActive\"><a id=\"aID6269\" href=\"#\" OnMouseOver=\"link('_dir','list0',this)\" class=\"leftMenuLinkHeadInActive\">list</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID728\" class=\"leftMenuInActive\"><a id=\"aID728\" href=\"#\" OnMouseOver=\"link('_class','List6216',this)\" class=\"leftMenuLinkInActive\">List<></a></div>\n");
document.write("<div id=\"divID729\" class=\"leftMenuInActive\"><a id=\"aID729\" href=\"#\" OnMouseOver=\"link('_class','ListItem6216',this)\" class=\"leftMenuLinkInActive\">ListItem<></a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Attributes</div>\n");
document.write("<div id=\"divID1127\" class=\"leftMenuInActive\"><a id=\"aID1127\" href=\"#\" OnMouseOver=\"link('_member','List7578827',this)\" class=\"leftMenuLinkInActive\">List</a></div>\n");
document.write("<div id=\"divID1126\" class=\"leftMenuInActive\"><a id=\"aID1126\" href=\"#\" OnMouseOver=\"link('_member','ListItem7578827',this)\" class=\"leftMenuLinkInActive\">ListItem</a></div>\n");
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
