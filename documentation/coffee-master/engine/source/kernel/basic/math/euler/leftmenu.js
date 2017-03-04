function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6284\" class=\"headerLeftMenuInActive\"><a id=\"aID6284\" href=\"#\" OnMouseOver=\"link('_dir','euler0',this)\" class=\"leftMenuLinkHeadInActive\">euler</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID744\" class=\"leftMenuInActive\"><a id=\"aID744\" href=\"#\" OnMouseOver=\"link('_class','Euler39014',this)\" class=\"leftMenuLinkInActive\">Euler</a></div>\n");
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
