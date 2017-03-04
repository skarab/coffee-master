function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6401\" class=\"headerLeftMenuInActive\"><a id=\"aID6401\" href=\"#\" OnMouseOver=\"link('_dir','mesh0',this)\" class=\"leftMenuLinkHeadInActive\">mesh</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID920\" class=\"leftMenuInActive\"><a id=\"aID920\" href=\"#\" OnMouseOver=\"link('_class','Mesh14855',this)\" class=\"leftMenuLinkInActive\">Mesh</a></div>\n");
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
