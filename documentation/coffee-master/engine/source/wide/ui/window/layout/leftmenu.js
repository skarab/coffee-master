function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6465\" class=\"headerLeftMenuInActive\"><a id=\"aID6465\" href=\"#\" OnMouseOver=\"link('_dir','layout0',this)\" class=\"leftMenuLinkHeadInActive\">layout</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID1042\" class=\"leftMenuInActive\"><a id=\"aID1042\" href=\"#\" OnMouseOver=\"link('_class','Layout49249',this)\" class=\"leftMenuLinkInActive\">Layout</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6254\" class=\"leftMenuInActive\"><a id=\"aID6254\" href=\"#\" OnMouseOver=\"link('_member','LAYOUT_STYLE121877613',this)\" class=\"leftMenuLinkInActive\">LAYOUT_STYLE</a></div>\n");
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
