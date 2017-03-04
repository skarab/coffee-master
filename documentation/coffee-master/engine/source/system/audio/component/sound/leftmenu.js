function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6340\" class=\"headerLeftMenuInActive\"><a id=\"aID6340\" href=\"#\" OnMouseOver=\"link('_dir','sound0',this)\" class=\"leftMenuLinkHeadInActive\">sound</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID841\" class=\"leftMenuInActive\"><a id=\"aID841\" href=\"#\" OnMouseOver=\"link('_class','ComponentSound45182',this)\" class=\"leftMenuLinkInActive\">ComponentSound</a></div>\n");
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
