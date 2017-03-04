function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6353\" class=\"headerLeftMenuInActive\"><a id=\"aID6353\" href=\"#\" OnMouseOver=\"link('_dir','sky0',this)\" class=\"leftMenuLinkHeadInActive\">sky</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID855\" class=\"leftMenuInActive\"><a id=\"aID855\" href=\"#\" OnMouseOver=\"link('_class','ComponentSky54809',this)\" class=\"leftMenuLinkInActive\">ComponentSky</a></div>\n");
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
