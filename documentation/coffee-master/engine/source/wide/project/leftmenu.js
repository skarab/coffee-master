function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6426\" class=\"headerLeftMenuInActive\"><a id=\"aID6426\" href=\"#\" OnMouseOver=\"link('_dir','project0',this)\" class=\"leftMenuLinkHeadInActive\">project</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID959\" class=\"leftMenuInActive\"><a id=\"aID959\" href=\"#\" OnMouseOver=\"link('_class','Project3886',this)\" class=\"leftMenuLinkInActive\">Project</a></div>\n");
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
