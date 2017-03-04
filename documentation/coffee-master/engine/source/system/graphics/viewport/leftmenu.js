function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6386\" class=\"headerLeftMenuInActive\"><a id=\"aID6386\" href=\"#\" OnMouseOver=\"link('_dir','viewport0',this)\" class=\"leftMenuLinkHeadInActive\">viewport</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID896\" class=\"leftMenuInActive\"><a id=\"aID896\" href=\"#\" OnMouseOver=\"link('_class','Viewport54809',this)\" class=\"leftMenuLinkInActive\">Viewport</a></div>\n");
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
